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

      for (std::vector<int8_t>::const_iterator it=data.begin();it!=data.end();++it) {
        ps << *it;
      }

      ps << static_cast<int8_t>(0x7F);
    }
  };

  class Packet_Server_0x19 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    std::string title;
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t direction;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> title >> x >> y >> z >> direction;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << title << x << y << z << direction;
    }
  };

  class Packet_Server_0x1A : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int32_t x;
    int32_t y;
    int32_t z;
    int16_t count;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> x >> y >> z >> count;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << x << y << z << count;
    }
  };

  class Packet_Server_0x1C : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int16_t velocityX;
    int16_t velocityY;
    int16_t velocityZ;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> velocityX >> velocityY >> velocityZ;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << velocityX << velocityY << velocityZ;
    }
  };

  class Packet_Server_0x1D : public Mineserver::Packet
  {
  public:
    int32_t entityId;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId;
    }
  };

  class Packet_Server_0x1E : public Mineserver::Packet
  {
  public:
    int32_t entityId;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId;
    }
  };

  class Packet_Server_0x1F : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t x;
    int8_t y;
    int8_t z;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> x >> y >> z;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << x << y << z;
    }
  };

  class Packet_Server_0x20 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t yaw;
    int8_t pitch;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> yaw >> pitch;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << yaw << pitch;
    }
  };

  class Packet_Server_0x21 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t x;
    int8_t y;
    int8_t z;
    int8_t yaw;
    int8_t pitch;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> x >> y >> z >> yaw >> pitch;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << x << y << z << yaw << pitch;
    }
  };

  class Packet_Server_0x22 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int32_t x;
    int32_t y;
    int32_t z;
    int8_t yaw;
    int8_t pitch;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> x >> y >> z >> yaw >> pitch;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << x << y << z << yaw << pitch;
    }
  };

  class Packet_Server_0x26 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t status;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> status;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << status;
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

  class Packet_Server_0x28 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    std::vector<int8_t> data;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId;

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
      ps << pid << entityId;

      for (std::vector<int8_t>::const_iterator it=data.begin();it!=data.end();++it) {
        ps << *it;
      }

      ps << static_cast<int8_t>(0x7F);
    }
  };

  class Packet_Server_0x29 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t effectId;
    int8_t amplifier;
    int16_t duration;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> effectId >> amplifier >> duration;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << effectId << amplifier << duration;
    }
  };

  class Packet_Server_0x2A : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    int8_t effectId;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> effectId;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << effectId;
    }
  };

  class Packet_Server_0x2B : public Mineserver::Packet
  {
  public:
    int8_t currentExperience;
    int8_t level;
    int16_t totalExperience;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> currentExperience >> level >> totalExperience;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << currentExperience << level << totalExperience;
    }
  };

  class Packet_Server_0x32 : public Mineserver::Packet
  {
  public:
    int16_t x;
    int16_t z;
    bool mode;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> x >> z >> mode;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << x << z << mode;
    }
  };

  class Packet_Server_0x33 : public Mineserver::Packet
  {
  public:
    int32_t posX;
    int16_t posY;
    int32_t posZ;
    int8_t sizeX;
    int8_t sizeY;
    int8_t sizeZ;
    int32_t bytes;
    std::vector<uint8_t> data;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> posX >> posY >> posZ >> sizeX >> sizeY >> sizeZ >> bytes;
      data.reserve(bytes);
      ps.bytesTo(reinterpret_cast<uint8_t*>(&(data[0])), bytes);
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << posX << posY << posZ << sizeX << sizeY << sizeZ << bytes;
      ps.bytesFrom(reinterpret_cast<uint8_t*>(&(data[0])), bytes);
    }
  };

  class Packet_Server_0x34 : public Mineserver::Packet
  {
  public:
    int32_t x;
    int32_t z;
    int16_t num;
    std::vector<int16_t> coordinate;
    std::vector<int8_t> type;
    std::vector<int8_t> meta;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> x >> z >> num;
      coordinate.reserve(num*2);
      ps.bytesTo(reinterpret_cast<uint8_t*>(&(coordinate[0])), num*2);
      type.reserve(num);
      ps.bytesTo(reinterpret_cast<uint8_t*>(&(type[0])), num);
      meta.reserve(num);
      ps.bytesTo(reinterpret_cast<uint8_t*>(&(meta[0])), num);
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << x << z << num;
      ps.bytesFrom(reinterpret_cast<uint8_t*>(&(coordinate[0])), num*2);
      ps.bytesFrom(reinterpret_cast<uint8_t*>(&(type[0])), num);
      ps.bytesFrom(reinterpret_cast<uint8_t*>(&(meta[0])), num);
    }
  };

  class Packet_Server_0x35 : public Mineserver::Packet
  {
  public:
    int32_t x;
    int8_t y;
    int32_t z;
    int8_t type;
    int8_t meta;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> x >> y >> z >> type >> meta;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << x << y << z << type << meta;
    }
  };

  class Packet_Server_0x36 : public Mineserver::Packet
  {
  public:
    int32_t x;
    int8_t y;
    int32_t z;
    int8_t data1;
    int8_t data2;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> x >> y >> z >> data1 >> data2;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << x << y << z << data1 << data2;
    }
  };

  class Packet_Server_0x3C : public Mineserver::Packet
  {
  public:
    double x;
    double y;
    double z;
    float unknown;
    int32_t count;
    std::vector<uint8_t> data;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> x >> y >> z >> unknown >> count;
      data.reserve(count*3);
      ps.bytesTo(reinterpret_cast<uint8_t*>(&(data[0])), count*3);
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << x << y << z << unknown << count;
      ps.bytesFrom(reinterpret_cast<uint8_t*>(&(data[0])), count*3);
    }
  };

  class Packet_Server_0x3D : public Mineserver::Packet
  {
  public:
    int32_t effectId;
    int32_t x;
    int8_t y;
    int32_t z;
    int32_t data;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> effectId >> x >> y >> z >> data;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << effectId << x << y << z << data;
    }
  };

  class Packet_Server_0x46 : public Mineserver::Packet
  {
  public:
    int8_t reason;
    int8_t mode;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> reason >> mode;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << reason << mode;
    }
  };

  class Packet_Server_0x47 : public Mineserver::Packet
  {
  public:
    int32_t entityId;
    bool unknown;
    int32_t x;
    int32_t y;
    int32_t z;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> entityId >> unknown >> x >> y >> z;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << entityId << unknown << x << y << z;
    }
  };

  class Packet_Server_0x64 : public Mineserver::Packet
  {
  public:
    int8_t windowId;
    int8_t inventoryType;
    std::string title;
    int8_t slots;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> windowId >> inventoryType >> title >> slots;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << windowId << inventoryType << title << slots;
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

  class Packet_Server_0x67 : public Mineserver::Packet
  {
  public:
    int8_t windowId;
    int16_t slot;
    int16_t itemId;
    int8_t count;
    int16_t uses;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> windowId >> slot >> itemId;

      if (itemId != -1) {
        ps >> count >> uses;
      }

      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << windowId << slot << itemId;

      if (itemId != -1) {
        ps << count << uses;
      }
    }
  };

  class Packet_Server_0x68 : public Mineserver::Packet
  {
  public:
    int8_t windowId;
    int16_t count;
    std::vector< std::pair< int16_t, std::pair< int8_t, int16_t > > > slots;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> windowId >> count;

      int16_t itemId, uses;
      int8_t count;

      for (int16_t i=0;i<count;++i) {
        itemId = uses = count = 0;

        ps >> itemId;

        if (itemId != -1) {
          ps >> count >> uses;
        }

        slots.push_back(std::pair<int16_t, std::pair<int8_t, int16_t> >(itemId, std::pair<int8_t, int16_t>(count, uses)));
      }

      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << windowId << count;

      int16_t itemId, uses;
      int8_t count;

      for (std::vector<std::pair<int16_t, std::pair<int8_t, int16_t> > >::const_iterator it=slots.begin();it!=slots.end();++it) {
        ps << it->first;

        if (it->first != -1) {
          ps << it->second.first << it->second.second;
        }
      }
    }
  };

  class Packet_Server_0x69 : public Mineserver::Packet
  {
  public:
    int8_t windowId;
    int16_t progressBarId;
    int16_t value;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> windowId >> progressBarId >> value;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << windowId << progressBarId << value;
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

  class Packet_Server_0x83 : public Mineserver::Packet
  {
  public:
    int16_t type;
    int16_t itemId;
    uint8_t len;
    std::vector<uint8_t> data;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> type >> itemId >> len;
      data.reserve(len);
      ps.bytesTo(reinterpret_cast<uint8_t*>(&(data[0])), len);
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << type << itemId << len;
      ps.bytesFrom(reinterpret_cast<uint8_t*>(&(data[0])), len);
    }
  };

  class Packet_Server_0xC8 : public Mineserver::Packet
  {
  public:
    int16_t statisticId;
    int8_t amount;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> statisticId >> amount;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << statisticId << amount;
    }
  };

  class Packet_Server_0xC9 : public Mineserver::Packet
  {
  public:
    std::string name;
    bool online;
    int16_t ping;
  public:
    void read(Mineserver::PacketStream& ps)
    {
      ps >> pid >> name >> online >> ping;
      ps.remove();
    }
    void write(Mineserver::PacketStream& ps)
    {
      ps << pid << name << online << ping;
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
