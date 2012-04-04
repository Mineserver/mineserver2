/*
  Copyright (c) 2011-2012, The Mineserver Project
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the The Mineserver Project nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <stdarg.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>

#include <mineserver/byteorder.h>
#include <mineserver/localization.h>
#include <mineserver/network/client.h>
#include <mineserver/network/message/keepalive.h>
#include <mineserver/network/message/kick.h>
#include <mineserver/network/message/chat.h>

void Mineserver::Network_Client::run()
{
  m_inactiveTicks++;
  m_inactiveTicksReply++;

  // client disconnects after one minute of us not responding.
  // we do not have to reply with the same keepalive id that they sent us.
  // --
  // we shall send this 3 times per minute, if we need more, increase this.
  // 1200 ticks = 1 minute, 400 ticks = 20 seconds, 20 * 3 = 1 minute
  // client has 3 times to see if we are responding or not.
  if (m_inactiveTicksReply >= 400)
  {
    boost::shared_ptr<Mineserver::Network_Message_KeepAlive> response = boost::make_shared<Mineserver::Network_Message_KeepAlive>();
    response->mid = 0x00;
    response->keepalive_id = 0;
    this->outgoing().push_back(response);
    resetInactiveTicksReply();
  }
}

void Mineserver::Network_Client::resetInactiveTicks()
{
  m_inactiveTicks = 0;
}

void Mineserver::Network_Client::resetInactiveTicksReply()
{
  m_inactiveTicksReply = 0;
}

void Mineserver::Network_Client::timedOut()
{
  boost::shared_ptr<Mineserver::Network_Message_Kick> responseMessage(new Mineserver::Network_Message_Kick);
  responseMessage->mid = 0xFF;
  responseMessage->reason = "Timed-out";
  this->outgoing().push_back(responseMessage);
  this->stop();
  // Jailout2000: Does the kick message get sent before closing the socket? I guess it doesn't *really* matter...
}

void Mineserver::Network_Client::start()
{
  this->read();
}

void Mineserver::Network_Client::stop()
{
  m_socket.close();
  m_alive = false;
}

void Mineserver::Network_Client::read()
{
  m_socket.async_read_some(
    boost::asio::buffer(m_tmp),
    boost::bind(
      &Mineserver::Network_Client::handleRead,
      shared_from_this(),
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred
    )
  );
}

void Mineserver::Network_Client::write()
{
  for (std::vector<Mineserver::Network_Message::pointer_t>::iterator it=m_outgoing.begin();it!=m_outgoing.end();++it) {
    printf("Trying to send message ID: %02x\n", (*it)->mid);
    m_protocol->compose(m_outgoingBuffer, **it);
  }

  m_outgoing.clear();

  printf("We want to send %lu bytes\n", m_outgoingBuffer.size());

  if (!m_writing)
  {
    m_writing = true;

    m_socket.async_write_some(
      boost::asio::buffer(m_outgoingBuffer),
      boost::bind(
        &Mineserver::Network_Client::handleWrite,
        shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred
      )
    );
  }
}

void Mineserver::Network_Client::handleRead(const boost::system::error_code& e, size_t n)
{
  if (!e) {
    m_incomingBuffer.insert(m_incomingBuffer.end(), m_tmp.begin(), m_tmp.begin() + n);

    printf("Got bytes: ");
    for (boost::array<uint8_t, 8192>::iterator it=m_tmp.begin();it!=m_tmp.begin()+n;++it) {
      printf("%02x", *it);
    }
    printf("\n");

    int state;
    do {
      Mineserver::Network_Message* message = NULL;

      state = m_protocol->parse(m_incomingBuffer, &message);

      if (state == Mineserver::Network_Protocol::STATE_GOOD) {
        m_incoming.push_back(Mineserver::Network_Message::pointer_t(message));
      }

      printf("State is: %d\n", state);
    } while (state == Mineserver::Network_Protocol::STATE_GOOD);

    read();
  } else if (e != boost::asio::error::operation_aborted) {
    stop();
  }
}

void Mineserver::Network_Client::handleWrite(const boost::system::error_code& e, size_t n)
{
	m_outgoingBuffer.erase(m_outgoingBuffer.begin(), m_outgoingBuffer.begin() + n);

  printf("Wrote %lu bytes, %lu left\n", n, m_outgoingBuffer.size());

  m_writing = false;

  if (m_outgoingBuffer.size() > 0) {
    write();
  }
}

void Mineserver::Network_Client::Message(const std::string &str)
{
  boost::shared_ptr<Mineserver::Network_Message_Chat> chatMessage(new Mineserver::Network_Message_Chat);
  chatMessage->mid = 0x03;
  chatMessage->message = str;
  this->outgoing().push_back(chatMessage);
}

void Mineserver::Network_Client::Message(const char* fmt, ...)
{
  va_list args;
  char buffer[65535] = "";
  if(fmt)
  {
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    this->Message(std::string(buffer));
    va_end(args);
  }
}

void Mineserver::Network_Client::Kick(const std::string &str)
{
  boost::shared_ptr<Mineserver::Network_Message_Kick> response(new Mineserver::Network_Message_Kick);
  response->mid = 0xFF;
  response->reason = str;
  this->outgoing().push_back(response);
}

void Mineserver::Network_Client::Kick(const char* fmt, ...)
{
  va_list args;
  char buffer[65535] = "";
  if(fmt)
  {
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    this->Kick(std::string(buffer));
    va_end(args);
  }
}
