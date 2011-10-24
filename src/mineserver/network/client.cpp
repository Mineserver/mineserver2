/*
  Copyright (c) 2011, The Mineserver Project
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

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include <mineserver/byteorder.h>
#include <mineserver/network/client.h>

void Mineserver::Network_Client::start()
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

void Mineserver::Network_Client::stop()
{
  m_socket.close();
  m_alive = false;
}

void Mineserver::Network_Client::send()
{
  boost::shared_ptr< std::vector<uint8_t> > buffer(new std::vector<uint8_t>);

  for (std::list<Mineserver::Network_Message::pointer_t>::iterator it=m_outgoing.begin();it!=m_outgoing.end();++it) {
    printf("Trying to send message ID %02x\n", (*it)->mid);
    m_protocol->compose(*buffer, **it);
  }

  m_outgoing.clear();

  printf("We want to send %d bytes\n", buffer->size());

  if (buffer->size() > 0)
  {
    m_socket.async_write_some(
      boost::asio::buffer(*buffer),
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

    int state;
    do {
      Mineserver::Network_Message* message = NULL;

      state = m_protocol->parse(m_incomingBuffer, &message);

      if (state == Mineserver::Network_Protocol::STATE_GOOD) {
        m_incoming.push_back(Mineserver::Network_Message::pointer_t(message));
      }
    } while (state == Mineserver::Network_Protocol::STATE_GOOD);
  } else if (e != boost::asio::error::operation_aborted) {
    stop();
  }
}

void Mineserver::Network_Client::handleWrite(const boost::system::error_code& e, size_t n)
{
  printf("Wrote %d bytes\n", n);
}
