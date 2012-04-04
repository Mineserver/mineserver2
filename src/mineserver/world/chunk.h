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

#ifndef MINESERVER_WORLD_CHUNK_H
#define MINESERVER_WORLD_CHUNK_H

#include <boost/shared_ptr.hpp>

#include <mineserver/byteorder.h>

#define CHUNK_INDEX(x,y,z) (y + (x << 7) + (z << 11))

namespace Mineserver
{
  struct World_ChunkPosition
  {
    int8_t x;
    int8_t y;
    int8_t z;

    World_ChunkPosition(int32_t _x, int16_t _y, int32_t _z) : x(_x),y(_y),z(_z) {}
    World_ChunkPosition() : x(0),y(0),z(0) {}
    World_ChunkPosition(const World_ChunkPosition& other) : x(other.x),y(other.y),z(other.z) {}

    Mineserver::World_ChunkPosition& operator=(const Mineserver::World_ChunkPosition& other)
    {
      if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
      }

      return *this;
    }
  };
  
  struct World_Chunk
  {
    typedef boost::shared_ptr<Mineserver::World_Chunk> pointer_t;

    uint32_t x;
    uint32_t z;

    // TODO:
    // This should use the worldHeight property instead of using 128 verbatim.
    uint8_t m_blockType[16*16*128];
    uint8_t m_blockMeta[16*16*128];
    uint8_t m_lightSky[16*16*128];
    uint8_t m_lightBlock[16*16*128];

    uint8_t getBlockType(uint8_t x, uint8_t y, uint8_t z) { return m_blockType[CHUNK_INDEX(x,y,z)]; }
    void setBlockType(uint8_t x, uint8_t y, uint8_t z, uint8_t blockType) { m_blockType[CHUNK_INDEX(x,y,z)] = blockType; }
    uint8_t getBlockMeta(uint8_t x, uint8_t y, uint8_t z) { return m_blockMeta[CHUNK_INDEX(x,y,z)]; }
    void setBlockMeta(uint8_t x, uint8_t y, uint8_t z, uint8_t blockMeta) { m_blockMeta[CHUNK_INDEX(x,y,z)] = blockMeta; }
    uint8_t getLightSky(uint8_t x, uint8_t y, uint8_t z) { return m_lightSky[CHUNK_INDEX(x,y,z)]; }
    void setLightSky(uint8_t x, uint8_t y, uint8_t z, uint8_t lightSky) { m_lightSky[CHUNK_INDEX(x,y,z)] = lightSky; }
    uint8_t getLightBlock(uint8_t x, uint8_t y, uint8_t z) { return m_lightBlock[CHUNK_INDEX(x,y,z)]; }
    void setLightBlock(uint8_t x, uint8_t y, uint8_t z, uint8_t lightBlock) { m_lightBlock[CHUNK_INDEX(x,y,z)] = lightBlock; }
  };
}

#endif

