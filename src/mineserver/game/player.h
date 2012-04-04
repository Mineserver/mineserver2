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

#ifndef MINESERVER_GAME_PLAYER_H
#define MINESERVER_GAME_PLAYER_H

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace Mineserver
{
  struct Game_PlayerPosition
  {
    double x;
    double y;
    double z;
    double stance;
    float pitch;
    float yaw;
    bool onGround;

    Game_PlayerPosition(double _x, double _y, double _z, double _stance, float _pitch, float _yaw, bool _onGround) : x(_x),y(_y),z(_z),stance(_stance),pitch(_pitch),yaw(_yaw),onGround(_onGround) {}
    Game_PlayerPosition(double _x, double _y, double _z) : x(_x),y(_y),z(_z),stance(0),pitch(0),yaw(0),onGround(0) {}
    Game_PlayerPosition() : x(0),y(0),z(0),stance(0),pitch(0),yaw(0),onGround(0) {}

    Mineserver::Game_PlayerPosition& operator= (const Mineserver::Game_PlayerPosition& other)
    {
      if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        stance = other.stance;
        pitch = other.pitch;
        yaw = other.yaw;
        onGround = other.onGround;
      }

      return *this;
    }
  };

  class Game_Player : public boost::enable_shared_from_this<Mineserver::Game_Player>
  {
  public:
    typedef boost::shared_ptr<Mineserver::Game_Player> pointer_t;

  private:
    std::string m_name;
    int32_t m_eid;
    Mineserver::Game_PlayerPosition m_position;

  public:
    const std::string& getName() { return m_name; }
    void setName(const std::string& name) { m_name.assign(name); }
    int32_t getEid() { return m_eid; }
    void setEid(int32_t eid) { m_eid = eid; }
    Mineserver::Game_PlayerPosition& getPosition() { return m_position; }
    void setPosition(Mineserver::Game_PlayerPosition pos) { m_position = pos; }

    void run();
    void shutdown();
  };
}

#endif
