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

#ifndef MINESERVER_GAME_OBJECT_BLOCK_H
#define MINESERVER_GAME_OBJECT_BLOCK_H

#include <mineserver/byteorder.h>
#include <mineserver/world.h>
#include <mineserver/world/chunk.h>

namespace Mineserver
{
  struct Game_Object_Block
  {
    private:
      Mineserver::World m_world;
      Mineserver::WorldBlockPosition m_pos;

    public:
      Game_Object_Block(Mineserver::World world, Mineserver::WorldBlockPosition pos) : m_world(world),m_pos(pos) {}
      Game_Object_Block(Mineserver::World world, int32_t x, int16_t y, int32_t z) : m_world(world),m_pos(Mineserver::WorldBlockPosition(x, y, z)) {}

      uint8_t getBlockType() { return getChunk()->getBlockType(m_pos.x & 15, m_pos.y, m_pos.z & 15); }
      uint8_t getBlockMeta() { return getChunk()->getBlockMeta(m_pos.x & 15, m_pos.y, m_pos.z & 15); }
      uint8_t getBlockSkyLight() { return getChunk()->getLightSky(m_pos.x & 15, m_pos.y, m_pos.z & 15); }
      uint8_t getBlockLight() { return getChunk()->getLightBlock(m_pos.x & 15, m_pos.y, m_pos.z & 15); }

      void setBlockType(uint8_t blockType) { getChunk()->setBlockType(m_pos.x & 15, m_pos.y, m_pos.z & 15, blockType); }
      void setBlockMeta(uint8_t blockMeta) { getChunk()->setBlockMeta(m_pos.x & 15, m_pos.y, m_pos.z & 15, blockMeta); }
      void setBlockSkyLight(uint8_t blockSkyLight) { getChunk()->setLightSky(m_pos.x & 15, m_pos.y, m_pos.z & 15, blockSkyLight); }
      void setBlockLight(uint8_t blockLight) { getChunk()->setLightBlock(m_pos.x & 15, m_pos.y, m_pos.z & 15, blockLight); }

    private:
      Mineserver::World_Chunk getChunk()
      {
        int32_t chunk_x = ((m_pos.x) >> 4);
        int32_t chunk_z = ((m_pos.z) >> 4);

        if (!m_world->hasChunk(chunk_x, chunk_z)) { return NULL; }

        return m_world->getChunk(chunk_x, chunk_z);
      }
  };
}

#endif
