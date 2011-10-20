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

#ifndef _PACKET_SERVER_H
#define _PACKET_SERVER_H

#include "byteorder.h"
#include "packetstream.h"
#include "packet.h"

namespace Mineserver
{
  class Packet_Server_0x00 : public Mineserver::Packet
  {
  public:
    int16_t id;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> id;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << id;
    }
  };

  class Packet_Server_0x01 : public Mineserver::Packet
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
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> version >> username >> junk_a >> junk_b >> junk_c >> junk_d >> junk_e >> junk_f;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << version << username << junk_a << junk_b << junk_c << junk_d << junk_e << junk_f;
    }
  };

  class Packet_Server_0x02 : public Mineserver::Packet
  {
  public:
    std::string username;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> username;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << username;
    }
  };

  class Packet_Server_0x03 : public Mineserver::Packet
  {
  public:
    std::string message;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> message;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << message;
    }
  };

  class Packet_Server_0x04 : public Mineserver::Packet
  {
  public:
    int64_t time;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> time;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << time;
    }
  };

  class Packet_Server_0x05 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int16_t slot;
    int16_t itemId;
    int16_t damage;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> slot >> itemId >> damage;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << slot << itemId << damage;
    }
  };

  class Packet_Server_0x06 : public Mineserver::Packet
  {
  public:
    int16_t x;
    int16_t y;
    int16_t z;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> x >> y >> z;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << x << y << z;
    }
  };

  class Packet_Server_0x08 : public Mineserver::Packet
  {
  public:
    int16_t health;
    int16_t food;
    float foodSaturation;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> health >> food >> foodSaturation;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << health << food << foodSaturation;
    }
  };

  class Packet_Server_0x09 : public Mineserver::Packet
  {
  public:
    int8_t world;
    int8_t difficulty;
    int8_t mode;
    int16_t height;
    int64_t seed;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> world >> difficulty >> mode >> height >> seed;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << world << difficulty << mode << height << seed;
    }
  };

  class Packet_Server_0x0A : public Mineserver::Packet
  {
  public:
    bool onGround;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> onGround;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << onGround;
    }
  };

  class Packet_Server_0x0B : public Mineserver::Packet
  {
  public:
    double x;
    double y;
    double stance;
    double z;
    bool onGround;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> x >> y >> stance >> z >> onGround;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << x << y << stance << z << onGround;
    }
  };

  class Packet_Server_0x0C : public Mineserver::Packet
  {
  public:
    float yaw;
    float pitch;
    bool onGround;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> yaw >> pitch >> onGround;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << yaw << pitch << onGround;
    }
  };

  class Packet_Server_0x0D : public Mineserver::Packet
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
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> x >> y >> stance >> z >> yaw >> pitch >> onGround;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << x << y << stance << z << yaw << pitch << onGround;
    }
  };

  class Packet_Server_0x11 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t inBed;
    int32_t x;
    int16_t y;
    int32_t z;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> inBed >> x >> y >> z;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << inBed << x << y << z;
    }
  };

  class Packet_Server_0x12 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t animation;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> animation;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << animation;
    }
  };

  class Packet_Server_0x14 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    std::string name;
    int32_t x;
    int32_t y;
    int32_t z;
    int8_t rotation;
    int8_t pitch;
    int16_t currentItem;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> name >> x >> y >> z >> rotation >> pitch >> currentItem;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << name << x << y << z << rotation << pitch << currentItem;
    }
  };

  class Packet_Server_0x15 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int16_t itemId;
    int8_t count;
    int16_t data;
    int32_t x;
    int32_t y;
    int32_t z;
    int8_t rotation;
    int8_t pitch;
    int16_t currentItem;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> itemId >> count >> data >> x >> y >> z >> rotation >> pitch >> currentItem;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << itemId << count << data << x << y << z << rotation << pitch << currentItem;
    }
  };

  class Packet_Server_0x16 : public Mineserver::Packet
  {
  public:
    int32_t collectedId;
    int32_t collectorId;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> collectedId >> collectorId;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << collectedId << collectorId;
    }
  };

  class Packet_Server_0x17 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t type;
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t throwerId;
    int16_t unknown1;
    int16_t unknown2;
    int16_t unknown3;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> type >> x >> y >> z >> throwerId;

      if (throwerId > 0) {
        ps >> unknown1 >> unknown2 >> unknown3;
      }

      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << type << x << y << z << throwerId;

      if (throwerId > 0) {
        ps << unknown1 << unknown2 << unknown3;
      }
    }
  };

  class Packet_Server_0x18 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t type;
    int32_t x;
    int32_t y;
    int32_t z;
    int8_t yaw;
    int8_t pitch;
    std::vector<int8_t> data;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> type >> x >> y >> z >> yaw >> pitch;

      int8_t tmp;
      while (true) {
        ps >> tmp;

        if (tmp == 0x7F) {
          break;
        } else {
          data.push_back(tmp);
        }
      }

      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << type << x << y << z << yaw << pitch;

      for (std::vector<int8_t>::iterator it=data.begin();it!=data.end();++it) {
        ps << *it;
      }

      ps << static_cast<int8_t>(0x7F);
    }
  };

  class Packet_Server_0x27 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int32_t vehicleId;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> vehicleId;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << vehicleId;
    }
  };

  class Packet_Server_0x65 : public Mineserver::Packet
  {
  public:
    int8_t windowId;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> windowId;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << windowId;
    }
  };

  class Packet_Server_0x66 : public Mineserver::Packet
  {
  public:
    int8_t windowId;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> windowId;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << windowId;
    }
  };

  class Packet_Server_0x6A : public Mineserver::Packet
  {
  public:
    int8_t windowId;
    int16_t action;
    bool accepted;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> windowId >> action >> accepted;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << windowId << action << accepted;
    }
  };

  class Packet_Server_0x6B : public Mineserver::Packet
  {
  public:
    int16_t slot;
    int16_t itemId;
    int16_t quantity;
    int16_t damage;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> slot >> itemId >> quantity >> damage;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << slot << itemId << quantity << damage;
    }
  };

  class Packet_Server_0x82 : public Mineserver::Packet
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
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> x >> y >> z >> line1 >> line2 >> line3 >> line4;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << x << y << z << line1 << line2 << line3 << line4;
    }
  };

  class Packet_Server_0xFE : public Mineserver::Packet
  {
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid;
    }
  };

  class Packet_Server_0xFF : public Mineserver::Packet
  {
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid;
    }
  };
};

#endif
