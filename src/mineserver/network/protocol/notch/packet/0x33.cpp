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

#include <vector>
#include <cstdio>
#include <cstring>
#include <zlib.h>

#include <mineserver/byteorder.h>
#include <mineserver/network/message/chunk.h>
#include <mineserver/network/protocol/notch/packet.h>
#include <mineserver/network/protocol/notch/packet/0x33.h>

#include <mineserver/world/chunk.h>

int Mineserver::Network_Protocol_Notch_Packet_0x33::_read(Mineserver::Network_Protocol_Notch_PacketStream& ps, Mineserver::Network_Message** message)
{
  Mineserver::Network_Message_Chunk* msg = new Mineserver::Network_Message_Chunk;
  *message = msg;

  int16_t bytes;
  std::vector<uint8_t> data;

  ps >> msg->mid >> msg->posX >> msg->posY >> msg->posZ >> msg->sizeX >> msg->sizeY >> msg->sizeZ >> bytes;
  data.reserve(bytes);
  ps.bytesTo(reinterpret_cast<uint8_t*>(&(data[0])), bytes);

  return STATE_GOOD;
}

int Mineserver::Network_Protocol_Notch_Packet_0x33::_write(Mineserver::Network_Protocol_Notch_PacketStream& ps, const Mineserver::Network_Message& message)
{
  const Mineserver::Network_Message_Chunk* msg = static_cast<const Mineserver::Network_Message_Chunk*>(&message);
  
  uint8_t* chunk = new uint8_t[81920];
  uint8_t* blockType = chunk;
	memset(blockType, 0x00, 32768);
  uint8_t* blockMeta = chunk + 32768;
	memset(blockMeta, 0x00, 16384);
  uint8_t* lightBlock = chunk + 49152;
	memset(lightBlock, 0xFF, 16384);
  uint8_t* lightSky = chunk + 65536;
	memset(lightSky, 0xFF, 16384);

  for (int y = 0; y < 128; ++y) {
    for (int x = 0; x < 16; ++x) {
      for (int z = 0; z < 16; ++z) {
        blockType[y+(z*128)+(x*128*16)] = msg->chunk->getBlockType(x, y, z);
//        blockMeta[y+(z*128)+(x*128*16)] = 0x00; //(msg->chunk->getBlockMeta(x, y, z) << 4) + msg->chunk->getBlockMeta(x+1, y, z);
//        lightSky[y+(z*128)+(x*128*16)] = 0xFF; //(msg->chunk->getLightSky(x, y, z) << 4) + msg->chunk->getLightSky(x+1, y, z);
//        lightBlock[y+(z*128)+(x*128*16)] = 0xFF; //(msg->chunk->getLightBlock(x, y, z) << 4) + msg->chunk->getLightBlock(x+1, y, z);
      }
    }
  }

	uLong slen = 81920;
	uLongf dlen = compressBound(slen);
	uint8_t* compressed = new uint8_t[dlen];
	int result = compress(compressed, &dlen, chunk, slen);

  printf("Compressed data is %lu bytes\n", dlen);

  ps << msg->mid << msg->posX << msg->posY << msg->posZ << msg->sizeX << msg->sizeY << msg->sizeZ << static_cast<int32_t>(dlen);
  ps.bytesFrom(compressed, dlen);

	delete[] chunk;
	delete[] compressed;

  return STATE_GOOD;
}
