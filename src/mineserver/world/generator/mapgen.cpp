/*
 * Copyright (c) 2011-2012, The Mineserver Project
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 * Neither the name of the The Mineserver Project nor the
 *  names of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*This is the main file for generate maps
the generation will start from here and it
should keep everything together.

Plan:
  *Get libnoise working simple generation
  *Improve libnoise generation
  *Add threads for each chunk & world
  *Add some objects - trees ect.
  *Add caves
  *Add boimes
  *Add mob spawns (if necessary and if ready)
  *Add config
  *Add custom objects that are loaded from a file into
   the map when it is generated e.g in a .BOB format
  *Add more advanced object like villages & npc's
  *Possibly match up mc client boimes with server ones
*/


#include <mineserver/world/chunk.h>
#include <mineserver/world/generator/mapgen.h>

void Mineserver::mapGen::writeLandscape()
{

  //This is a bit scrapy, it will be updated soon

  uint8_t blockType;

  bool bWater;

  for(uint8_t x=0;x<16;x++)
  {
    for(uint8_t z=0;z<16;z++)
    {
      blockType = 0x07; //bedrock
      bWater = false;

      if(heightMap[x][z] < 1){heightMap[x][z] = 1;}
      else if(heightMap[x][z] > 127){heightMap[x][z] = 127;}

      for(uint8_t y=0;y<128;y++)
      {
        if(y==1){ blockType = 0x01;}//stone

        if(y == heightMap[x][z]-3)
        {
          if (y < 44){blockType = 0x0c;}//sand
          else {blockType = 0x03;}//dirt
        }

        if(y == heightMap[x][z])
        {
          if (y<41){blockType = 0x08;bWater = true;}//water
          else if (y>43) {blockType = 0x02;}//grass
        }

        if (bWater == true){
          if (y>40){blockType = 0x00;}//air
        }
        else if(y == heightMap[x][z] + 1)
        {
          blockType = 0x00;//air
        }

        chunk->setBlockType(x, y, z, blockType);
        chunk->setBlockMeta(x, y, z, 0);
      }
    }
  }

}

void Mineserver::mapGen::init(long seed)
{
  terrain_v.push_back(terrain_t(new worldGeneration::terrainGen));//don't know if a vector is the best
  terrain_v[0]->noiseInit(seed);

}

bool Mineserver::mapGen::processChunk(Mineserver::World_Chunk::pointer_t tempChunk,int32_t chunkX, int32_t chunkZ)
{
  chunk = tempChunk;

  std::cout << "processing chunk\n";

  terrain_v[0]->noiseWrite(heightMap,chunkX,chunkZ);
  writeLandscape();

  return true;

}
