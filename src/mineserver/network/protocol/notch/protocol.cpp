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

#include <vector>
#include <cstdio>

#include <mineserver/byteorder.h>
#include <mineserver/network/message.h>
#include <mineserver/network/message/0xFE.h>

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

#include <mineserver/network/protocol/notch/protocol.h>

int Mineserver::Network_Protocol_Notch_Protocol::parse(std::vector<uint8_t>& bytes, Mineserver::Network_Message** outmsg)
{
  if (bytes.size() < 1) {
    return Mineserver::Network_Protocol::STATE_STOP;
  }

  uint8_t id = bytes[0];

  printf("Found packet: %02x\n", id);

  m_packetStream.setBuffer(&bytes);
  m_packetStream.setPos(0);
  m_packetStream.setValid(true);

  Mineserver::Network_Protocol_Notch_Packet* packet = NULL;
  Mineserver::Network_Message* message = NULL;

  int state = Mineserver::Network_Protocol::STATE_ERROR;
  int packetState = Mineserver::Network_Protocol_Notch_Packet::STATE_ERROR;

  switch (id)
  {
    case 0x00:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x00 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x01:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x01 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x02:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x02 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x03:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x03 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x04:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x04 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x05:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x05 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x06:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x06 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x07:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x07 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x08:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x08 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x09:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x09 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x0A:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0A packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x0B:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0B packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x0C:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0C packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x0D:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0D packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x0E:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0E packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x0F:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0F packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x10:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x10 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x11:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x11 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x12:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x12 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x13:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x13 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x14:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x14 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x15:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x15 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x16:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x16 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x17:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x17 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x18:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x18 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x19:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x19 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x1A:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1A packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x1C:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1C packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x1D:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1D packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x1E:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1E packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x1F:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1F packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x20:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x20 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x21:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x21 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x22:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x22 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x26:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x26 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x27:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x27 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x28:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x28 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x29:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x29 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x2A:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x2A packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x2B:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x2B packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x32:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x32 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x33:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x33 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x34:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x34 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x35:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x35 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x36:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x36 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x3C:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x3C packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x3D:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x3D packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x46:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x46 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x47:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x47 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x64:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x64 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x65:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x65 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x66:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x66 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x67:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x67 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x68:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x68 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x69:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x69 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x6A:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x6A packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x6B:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x6B packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x82:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x82 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0x83:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x83 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0xC8:
    {
      Mineserver::Network_Protocol_Notch_Packet_0xC8 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0xC9:
    {
      Mineserver::Network_Protocol_Notch_Packet_0xC9 packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0xFE:
    {
      Mineserver::Network_Protocol_Notch_Packet_0xFE packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
    case 0xFF:
    {
      Mineserver::Network_Protocol_Notch_Packet_0xFF packet;
      packetState = packet.read(m_packetStream, &message);
      break;
    }
  }

  if (packetState == Mineserver::Network_Protocol_Notch_Packet::STATE_GOOD) {
    state = Mineserver::Network_Protocol::STATE_GOOD;
    *outmsg = message;
    m_packetStream.remove();
  } else if (packetState == Mineserver::Network_Protocol_Notch_Packet::STATE_STOP) {
    state = Mineserver::Network_Protocol::STATE_STOP;
    delete message;
  } else if (packetState == Mineserver::Network_Protocol_Notch_Packet::STATE_ERROR) {
    state = Mineserver::Network_Protocol::STATE_ERROR;
    delete message;
  }

  m_packetStream.reset();

  return state;
}

int Mineserver::Network_Protocol_Notch_Protocol::compose(std::vector<uint8_t>& bytes, const Mineserver::Network_Message& message)
{
  m_packetStream.setBuffer(&bytes);
  m_packetStream.setPos(0);

  switch (message.mid)
  {
    case 0x00:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x00 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x01:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x01 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x02:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x02 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x03:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x03 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x04:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x04 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x05:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x05 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x06:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x06 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x07:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x07 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x08:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x08 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x09:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x09 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x0A:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0A packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x0B:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0B packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x0C:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0C packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x0D:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0D packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x0E:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0E packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x0F:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x0F packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x10:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x10 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x11:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x11 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x12:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x12 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x13:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x13 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x14:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x14 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x15:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x15 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x16:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x16 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x17:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x17 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x18:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x18 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x19:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x19 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x1A:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1A packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x1C:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1C packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x1D:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1D packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x1E:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1E packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x1F:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x1F packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x20:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x20 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x21:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x21 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x22:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x22 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x26:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x26 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x27:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x27 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x28:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x28 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x29:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x29 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x2A:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x2A packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x2B:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x2B packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x32:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x32 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x33:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x33 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x34:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x34 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x35:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x35 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x36:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x36 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x3C:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x3C packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x3D:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x3D packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x46:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x46 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x47:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x47 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x64:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x64 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x65:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x65 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x66:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x66 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x67:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x67 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x68:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x68 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x69:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x69 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x6A:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x6A packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x6B:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x6B packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x82:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x82 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0x83:
    {
      Mineserver::Network_Protocol_Notch_Packet_0x83 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0xC8:
    {
      Mineserver::Network_Protocol_Notch_Packet_0xC8 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0xC9:
    {
      Mineserver::Network_Protocol_Notch_Packet_0xC9 packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0xFE:
    {
      Mineserver::Network_Protocol_Notch_Packet_0xFE packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
    case 0xFF:
    {
      Mineserver::Network_Protocol_Notch_Packet_0xFF packet;
      int packetState = packet.write(m_packetStream, message);
      break;
    }
  }

//	printf("Bytes: ");
//	for (int i = m_packetStream.getPos(); i < m_packetStream.getBuffer()->size(); ++i) {
//		printf("%02x", m_packetStream.getBuffer()->at(i));
//	}
//	printf("\n");

  m_packetStream.setBuffer(NULL);
  m_packetStream.setPos(0);

  return STATE_GOOD;
}
