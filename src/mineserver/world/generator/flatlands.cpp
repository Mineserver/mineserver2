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

#include <mineserver/world/chunk.h>
#include <mineserver/world/generator/flatlands.h>

bool Mineserver::World_Generator_Flatlands::processChunk(Mineserver::World_Chunk::pointer_t chunk)
{
  uint8_t blockType;

  for (uint8_t y=0;y<=127;++y) {
    switch (y)
    {
      case 0:
        blockType = 0x07; // Bedrock
        break;
      case 1:
        blockType = 0x01; // Stone
        break;
      case 54:
        blockType = 0x03; // Dirt
        break;
      case 59:
        blockType = 0x02; // Grass
        break;
      case 60:
        blockType = 0x00; // Air
        break;
    }

    for (uint8_t x=0;x<=15;++x) {
      for (uint8_t z=0;z<=15;++z) {
        chunk->setBlockType(x, y, z, blockType);
        chunk->setBlockMeta(x, y, z, 0);
      }
    }

  }

  return true;
}

