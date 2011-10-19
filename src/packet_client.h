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

#include "byteorder.h"
#include "packet.h"

namespace Mineserver
{
  class Packet_Client_0x00 : public Packet
  {
  public:
    int16_t id;
  public:
    void read(PacketStream& ps)
    {
      ps >> pid >> id;
      ps.remove();
    }
  };

  class Packet_Client_0x01 : public Packet
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
    void read(PacketStream& ps)
    {
      ps >> pid >> version >> username >> junk_a >> junk_b >> junk_c >> junk_d >> junk_e >> junk_f;
      ps.remove();
    }
  };

  class Packet_Client_0x02 : public Packet
  {
  public:
    std::string username;
  public:
    void read(PacketStream& ps)
    {
      ps >> pid >> username;
      ps.remove();
    }
  };

  class Packet_Client_0x03 : public Packet
  {
  public:
    std::string message;
  public:
    void read(PacketStream& ps)
    {
      ps >> pid >> message;
      ps.remove();
    }
  };

  class Packet_Client_0x07 : public Packet
  {
  public:
    int32_t user;
    int32_t target;
    bool leftClick;
  public:
    void read(PacketStream& ps)
    {
      ps >> pid >> user >> target >> leftClick;
      ps.remove();
    }
  };

  class Packet_Client_0x09 : public Packet
  {
  public:
    int8_t world;
    int8_t difficulty;
    int8_t mode;
    int16_t height;
    int64_t seed;
  public:
    void read(PacketStream& ps)
    {
      ps >> pid >> world >> difficulty >> mode >> height >> seed;
      ps.remove();
    }
  };

  class Packet_Client_0x0A : public Packet
  {
  public:
    bool onGround;
  public:
    void read(PacketStream& ps)
    {
      ps >> pid >> onGround;
      ps.remove();
    }
  };

  class Packet_Client_0x0B : public Packet
  {
  public:
    double x;
    double y;
    double stance;
    double z;
    bool onGround;
  public:
    void read(PacketStream& ps)
    {
      ps >> pid >> x >> y >> stance >> z >> onGround;
      ps.remove();
    }
  };

  class Packet_Client_0x0C : public Packet
  {
  public:
    float yaw;
    float pitch;
    bool onGround;
  public:
    void read(PacketStream& ps)
    {
      ps >> pid >> yaw >> pitch >> onGround;
      ps.remove();
    }
  };

  class Packet_Client_0x0D : public Packet
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
    void read(PacketStream& ps)
    {
      ps >> pid >> x >> y >> stance >> z >> yaw >> pitch >> onGround;
      ps.remove();
    }
    void write(PacketStream ps)
    {
      ps << pid << x << y << stance << z << yaw << pitch << onGround;
    }
  };

  class Packet_Client_0x0E : public Packet
  {
  public:
    int8_t status;
    int32_t x;
    int8_t y;
    int32_t z;
    int8_t face;
  public:
    void read(PacketStream& ps)
    {
      ps >> pid >> status >> x >> y >> z >> face;
      ps.remove();
    }
    void write(PacketStream ps)
    {
      ps << pid << status << x << y << z << face;
    }
  };

  class Packet_Client_0x0F : public Packet
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
    void read(PacketStream& ps)
    {
      ps >> pid >> x >> y >> z >> direction >> itemId >> amount >> damage;
      ps.remove();
    }
    void write(PacketStream ps)
    {
      ps << pid << x << y << z << direction << itemId << amount << damage;
    }
  };
}

#endif
