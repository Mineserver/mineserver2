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

#ifndef MINESERVER_WORLD_H
#define MINESERVER_WORLD_H

#include <boost/shared_ptr.hpp>

#include <mineserver/world/chunk.h>

namespace Mineserver
{
  struct World
  {
  public:
    typedef boost::shared_ptr<Mineserver::World> pointer_t;

    // Jailout2000: Are enums okay to use here?
    // If these enums stay, plugins will need access to them. (TODO)
    enum GameMode
    {
      survival = 0, creative = 1
    };
    enum Dimension
    {
      nether = -1, overWorld = 0, theEnd = 1
    };
    enum Difficulty
    {
      peaceful = 0, easy = 1, normal = 2, hard = 3
    };

    static const int8_t defaultGameMode = survival;
    static const int8_t defaultDimension = overWorld;
    static const int8_t defaultDifficulty = easy;
    static const uint8_t defaultWorldHeight = 127;

  private:
    std::map<std::pair<uint32_t,uint32_t>, Mineserver::World_Chunk::pointer_t> m_chunks;
    long worldSeed;
    GameMode gameMode;
    Dimension dimension;
    Difficulty difficulty;
    uint8_t worldHeight;

  public:
    bool hasChunk(uint32_t x, uint32_t z)
    {
      std::pair<uint32_t,uint32_t> coord(x,z);
      return Mineserver::World_Chunk::pointer_t(m_chunks[coord]);
    }

    Mineserver::World_Chunk::pointer_t getChunk(uint32_t x, uint32_t z)
    {
      std::pair<uint32_t,uint32_t> coord(x,z);
      return Mineserver::World_Chunk::pointer_t(m_chunks[coord]);
    }

    void setChunk(uint32_t x, uint32_t z, Mineserver::World_Chunk::pointer_t chunk)
    {
      std::pair<uint32_t,uint32_t> coord(x,z);
      m_chunks[coord] = chunk;
    }

    long getWorldSeed()
    {
      return worldSeed;
    }

    void setWorldSeed(long new_value)
    {
      worldSeed = new_value;
    }

    bool getGameMode()
    {
      return gameMode;
    }

    void setGameMode(GameMode new_value)
    {
      gameMode = new_value;
    }

    int getDimension()
    {
      return dimension;
    }

    void setDimension(Dimension new_value)
    {
      dimension = new_value;
    }

    int getDifficulty()
    {
      return difficulty;
    }

    void setDifficulty(Difficulty new_value)
    {
      difficulty = new_value;
    }

    int getWorldHeight()
    {
      return worldHeight;
    }

    void setWorldHeight(int new_value)
    {
      worldHeight = new_value;
    }
  };
}

#endif
