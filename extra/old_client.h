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

#ifndef _PACKET_CLIENT_H
#define _PACKET_CLIENT_H

#include <mineserver/byteorder.h>
#include <mineserver/network/notch/packetstream.h>
#include <mineserver/network/notch/packet.h>

namespace Mineserver
{
  struct Network_Protocol_Notch_Packet_Client_0x00 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int16_t id;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> id;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << id;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x01 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int32_t version;
    std::string username;
    int64_t junk_a;
    int32_t junk_b;
    int8_t junk_c;
    int8_t junk_d;
    uint8_t junk_e;
    uint8_t junk_f;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> version >> username >> junk_a >> junk_b >> junk_c >> junk_d >> junk_e >> junk_f;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << version << username << junk_a << junk_b << junk_c << junk_d << junk_e << junk_f;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x02 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    std::string username;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> username;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << username;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x03 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    std::string message;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> message;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << message;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x07 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int32_t user;
    int32_t target;
    bool leftClick;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> user >> target >> leftClick;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << user << target << leftClick;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x09 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int8_t world;
    int8_t difficulty;
    int8_t mode;
    int16_t height;
    int64_t seed;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> world >> difficulty >> mode >> height >> seed;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << world << difficulty << mode << height << seed;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x0A : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    bool onGround;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> onGround;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << onGround;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x0B : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    double x;
    double y;
    double stance;
    double z;
    bool onGround;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> x >> y >> stance >> z >> onGround;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << x << y << stance << z << onGround;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x0C : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    float yaw;
    float pitch;
    bool onGround;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> yaw >> pitch >> onGround;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << yaw << pitch << onGround;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x0D : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    double x;
    double y;
    double stance;
    double z;
    float yaw;
    float pitch;
    bool onGround;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> x >> y >> stance >> z >> yaw >> pitch >> onGround;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << x << y << stance << z << yaw << pitch << onGround;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x0E : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int8_t status;
    int32_t x;
    int8_t y;
    int32_t z;
    int8_t face;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> status >> x >> y >> z >> face;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << status << x << y << z << face;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x0F : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int32_t x;
    int8_t y;
    int32_t z;
    int8_t direction;
    int16_t itemId;
    int8_t amount;
    int16_t damage;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> x >> y >> z >> direction >> itemId >> amount >> damage;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << x << y << z << direction << itemId << amount << damage;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x10 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int16_t id;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> id;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << id;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x12 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int32_t entityId;
    int8_t animation;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> entityId >> animation;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << entityId << animation;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x13 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int32_t entityId;
    int8_t actionId;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> entityId >> actionId;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << entityId << actionId;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x27 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int32_t entityId;
    int32_t vehicleId;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> entityId >> vehicleId;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << entityId << vehicleId;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x65 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int8_t windowId;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> windowId;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << windowId;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x66 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int8_t windowId;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> windowId;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << windowId;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x6A : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int8_t windowId;
    int16_t action;
    bool accepted;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> windowId >> action >> accepted;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << windowId << action << accepted;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x6B : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int16_t slot;
    int16_t itemId;
    int16_t quantity;
    int16_t damage;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> slot >> itemId >> quantity >> damage;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << slot << itemId << quantity << damage;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0x82 : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    int32_t x;
    int16_t y;
    int32_t z;
    std::string line1;
    std::string line2;
    std::string line3;
    std::string line4;
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid >> x >> y >> z >> line1 >> line2 >> line3 >> line4;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid << x << y << z << line1 << line2 << line3 << line4;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0xFE : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid;
    }
  };

  struct Network_Protocol_Notch_Packet_Client_0xFF : public Mineserver::Network_Protocol_Notch_Packet
  {
  public:
    void read(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps >> pid;
      ps.remove();
    }
    void write(Mineserver::Network_Protocol_Notch_PacketStream& ps)
    {
      ps << pid;
    }
  };
};

#endif
