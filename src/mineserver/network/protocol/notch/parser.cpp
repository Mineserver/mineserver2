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

#include <vector>
#include <list>

#include <boost/shared_ptr.hpp>

#include <mineserver/network/message.h>
#include <mineserver/network/parser.h>

#include <mineserver/network/protocol/notch/packet.h>
#include <mineserver/network/protocol/notch/packet/0x00.h>
#include <mineserver/network/protocol/notch/packet/0x01.h>
#include <mineserver/network/protocol/notch/packet/0x02.h>
#include <mineserver/network/protocol/notch/packet/0x03.h>
#include <mineserver/network/protocol/notch/packet/0x04.h>
#include <mineserver/network/protocol/notch/packet/0x05.h>
#include <mineserver/network/protocol/notch/packet/0x06.h>
#include <mineserver/network/protocol/notch/packet/0x07.h>
#include <mineserver/network/protocol/notch/packet/0x08.h>
#include <mineserver/network/protocol/notch/packet/0x09.h>
#include <mineserver/network/protocol/notch/packet/0x0A.h>
#include <mineserver/network/protocol/notch/packet/0x0B.h>
#include <mineserver/network/protocol/notch/packet/0x0C.h>
#include <mineserver/network/protocol/notch/packet/0x0D.h>
#include <mineserver/network/protocol/notch/packet/0x0E.h>
#include <mineserver/network/protocol/notch/packet/0x0F.h>
#include <mineserver/network/protocol/notch/packet/0x10.h>
#include <mineserver/network/protocol/notch/packet/0x11.h>
#include <mineserver/network/protocol/notch/packet/0x12.h>
#include <mineserver/network/protocol/notch/packet/0x13.h>
#include <mineserver/network/protocol/notch/packet/0x14.h>
#include <mineserver/network/protocol/notch/packet/0x15.h>
#include <mineserver/network/protocol/notch/packet/0x16.h>
#include <mineserver/network/protocol/notch/packet/0x17.h>
#include <mineserver/network/protocol/notch/packet/0x18.h>
#include <mineserver/network/protocol/notch/packet/0x19.h>
#include <mineserver/network/protocol/notch/packet/0x1A.h>
#include <mineserver/network/protocol/notch/packet/0x1C.h>
#include <mineserver/network/protocol/notch/packet/0x1D.h>
#include <mineserver/network/protocol/notch/packet/0x1E.h>
#include <mineserver/network/protocol/notch/packet/0x1F.h>
#include <mineserver/network/protocol/notch/packet/0x20.h>
#include <mineserver/network/protocol/notch/packet/0x21.h>
#include <mineserver/network/protocol/notch/packet/0x22.h>
#include <mineserver/network/protocol/notch/packet/0x26.h>
#include <mineserver/network/protocol/notch/packet/0x27.h>
#include <mineserver/network/protocol/notch/packet/0x28.h>
#include <mineserver/network/protocol/notch/packet/0x29.h>
#include <mineserver/network/protocol/notch/packet/0x2A.h>
#include <mineserver/network/protocol/notch/packet/0x2B.h>
#include <mineserver/network/protocol/notch/packet/0x32.h>
#include <mineserver/network/protocol/notch/packet/0x33.h>
#include <mineserver/network/protocol/notch/packet/0x34.h>
#include <mineserver/network/protocol/notch/packet/0x35.h>
#include <mineserver/network/protocol/notch/packet/0x36.h>
#include <mineserver/network/protocol/notch/packet/0x3C.h>
#include <mineserver/network/protocol/notch/packet/0x3D.h>
#include <mineserver/network/protocol/notch/packet/0x46.h>
#include <mineserver/network/protocol/notch/packet/0x47.h>
#include <mineserver/network/protocol/notch/packet/0x64.h>
#include <mineserver/network/protocol/notch/packet/0x65.h>
#include <mineserver/network/protocol/notch/packet/0x66.h>
#include <mineserver/network/protocol/notch/packet/0x67.h>
#include <mineserver/network/protocol/notch/packet/0x68.h>
#include <mineserver/network/protocol/notch/packet/0x69.h>
#include <mineserver/network/protocol/notch/packet/0x6A.h>
#include <mineserver/network/protocol/notch/packet/0x6B.h>
#include <mineserver/network/protocol/notch/packet/0x82.h>
#include <mineserver/network/protocol/notch/packet/0x83.h>
#include <mineserver/network/protocol/notch/packet/0xC8.h>
#include <mineserver/network/protocol/notch/packet/0xC9.h>
#include <mineserver/network/protocol/notch/packet/0xFE.h>
#include <mineserver/network/protocol/notch/packet/0xFF.h>

#include <mineserver/network/protocol/notch/parser.h>

int Mineserver::Network_Protocol_Notch_Parser::read(std::vector<uint8_t>& bytes, std::list< boost::shared_ptr<Mineserver::Network_Message> >& messages)
{
  if (bytes.size() < 1) {
    return Mineserver::Network_Parser::STATE_DONE;
  }

  uint8_t id = bytes[0];

  boost::shared_ptr<Mineserver::Network_Message> message;
  boost::shared_ptr<Mineserver::Network_Protocol_Notch_Packet> packet;

  m_packetStream.setBuffer(&bytes);
  m_packetStream.setPos(0);

  int state = Mineserver::Network_Parser::STATE_ERROR;
  int packetState = Mineserver::Network_Protocol_Notch_Packet::STATE_ERROR;

  switch (id)
  {
  case 0xFE:
    packet = boost::shared_ptr<Mineserver::Network_Protocol_Notch_Packet_0xFE>(new Mineserver::Network_Protocol_Notch_Packet_0xFE);
    packetState = packet->read(m_packetStream);
    break;
  }

  if (packetState == Mineserver::Network_Protocol_Notch_Packet::STATE_MORE) {
    messages.push_back(boost::shared_ptr<Mineserver::Network_Message>(packet->message));
    m_packetStream.remove();
    state = Mineserver::Network_Parser::STATE_MORE;
  } else if (packetState == Mineserver::Network_Protocol_Notch_Packet::STATE_NEEDMOREDATA) {
    state = Mineserver::Network_Parser::STATE_DONE;
  } else if (packetState == Mineserver::Network_Protocol_Notch_Packet::STATE_ERROR) {
    state = Mineserver::Network_Parser::STATE_ERROR;
  }

  m_packetStream.setBuffer(NULL);
  m_packetStream.setPos(0);

  return state;
}
