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

#ifndef MINESERVER_GAME_WORLD_CHUNK_H
#define MINESERVER_GAME_WORLD_CHUNK_H

#include <boost/shared_ptr.hpp>

#include <mineserver/byteorder.h>

namespace Mineserver
{
  struct Game_World_Chunk
  {
    typedef boost::shared_ptr<Mineserver::Game_World_Chunk> pointer_t;

    uint32_t x;
    uint32_t z;

    // TODO:
    // This should use the worldHeight property instead of using 128 verbatim.
    uint8_t m_blockType[16*16*128];
    uint8_t m_blockMeta[16*16*128];
    uint8_t m_lightSky[16*16*128];
    uint8_t m_lightBlock[16*16*128];

    uint8_t getBlockType(uint8_t x, uint8_t y, uint8_t z) { return m_blockType[x + (y << 8) + (z << 16)]; }
    void setBlockType(uint8_t x, uint8_t y, uint8_t z, uint8_t blockType) { m_blockType[x + (y << 8) + (z << 16)] = blockType; }
    uint8_t getBlockMeta(uint8_t x, uint8_t y, uint8_t z) { return m_blockMeta[x + (y << 8) + (z << 16)]; }
    void setBlockMeta(uint8_t x, uint8_t y, uint8_t z, uint8_t blockMeta) { m_blockMeta[x + (y << 8) + (z << 16)] = blockMeta; }
    uint8_t getLightSky(uint8_t x, uint8_t y, uint8_t z) { return m_lightSky[x + (y << 8) + (z << 16)]; }
    void setLightSky(uint8_t x, uint8_t y, uint8_t z, uint8_t lightSky) { m_lightSky[x + (y << 8) + (z << 16)] = lightSky; }
    uint8_t getLightBlock(uint8_t x, uint8_t y, uint8_t z) { return m_lightBlock[x + (y << 8) + (z << 16)]; }
    void setLightBlock(uint8_t x, uint8_t y, uint8_t z, uint8_t lightBlock) { m_lightBlock[x + (y << 8) + (z << 16)] = lightBlock; }
  };
}

#endif
