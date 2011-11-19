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

#include <vector>
#include <cstdio>

#include <mineserver/byteorder.h>
#include <mineserver/network/message/chunk.h>
#include <mineserver/network/protocol/notch/packet.h>
#include <mineserver/network/protocol/notch/packet/0x33.h>

#include <mineserver/nbt.h>
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

  Mineserver::NBT nbt(Mineserver::NBT::TAG_COMPOUND);

  nbt.Insert("Blocks", new Mineserver::NBT(Mineserver::NBT::TAG_BYTE_ARRAY));
  nbt.Insert("Data", new Mineserver::NBT(Mineserver::NBT::TAG_BYTE_ARRAY));
  nbt.Insert("SkyLight", new Mineserver::NBT(Mineserver::NBT::TAG_BYTE_ARRAY));
  nbt.Insert("BlockLight", new Mineserver::NBT(Mineserver::NBT::TAG_BYTE_ARRAY));
  nbt.Insert("HeightMap", new Mineserver::NBT(Mineserver::NBT::TAG_BYTE_ARRAY));
  nbt.Insert("Entities", new Mineserver::NBT(Mineserver::NBT::TAG_LIST, Mineserver::NBT::TAG_COMPOUND));
  nbt.Insert("TileEntities", new Mineserver::NBT(Mineserver::NBT::TAG_LIST, Mineserver::NBT::TAG_COMPOUND));
  nbt.Insert("LastUpdate", new Mineserver::NBT(Mineserver::NBT::TAG_LONG));
  nbt.Insert("xPos", new Mineserver::NBT(Mineserver::NBT::TAG_INT));
  nbt.Insert("zPos", new Mineserver::NBT(Mineserver::NBT::TAG_INT));
  nbt.Insert("TerrainPopulated", new Mineserver::NBT(Mineserver::NBT::TAG_BYTE));

  *nbt["xPos"] = static_cast<int32_t>(msg->chunk->x);
  *nbt["zPos"] = static_cast<int32_t>(msg->chunk->z);

  std::vector<uint8_t>* blockType = nbt["Blocks"]->GetByteArray();
  std::vector<uint8_t>* blockMeta = nbt["Data"]->GetByteArray();
  std::vector<uint8_t>* lightSky = nbt["SkyLight"]->GetByteArray();
  std::vector<uint8_t>* lightBlock = nbt["BlockLight"]->GetByteArray();

  blockType->resize(128*16*16);
  blockMeta->resize(128*16*8);
  lightSky->resize(128*16*8);
  lightBlock->resize(128*16*8);

  for (int y = 0; y < 128; ++y) {
    for (int z = 0; z < 16; ++z) {
      for (int x = 0; x < 16; x += 2) {
        (*blockType)[y+(z*128)+(x*128*16)] = msg->chunk->getBlockType(x, y, z);
        (*blockType)[y+(z*128)+(x*128*16)+1] = msg->chunk->getBlockType(x+1, y, z);
        (*blockMeta)[y+(z*128)+((x/2)*128*8)] = (msg->chunk->getBlockMeta(x, y, z) << 4) + msg->chunk->getBlockMeta(x+1, y, z);
        (*lightSky)[y+(z*128)+((x/2)*128*8)] = (msg->chunk->getLightSky(x, y, z) << 4) + msg->chunk->getLightSky(x+1, y, z);
        (*lightBlock)[y+(z*128)+((x/2)*128*8)] = (msg->chunk->getLightBlock(x, y, z) << 4) + msg->chunk->getLightBlock(x+1, y, z);
      }
    }
  }

  std::vector<uint8_t> data;

  nbt.Write(data);
  int16_t bytes = data.size();

  printf("NBT data is %d bytes\n", bytes);

  ps << msg->mid << msg->posX << msg->posY << msg->posZ << msg->sizeX << msg->sizeY << msg->sizeZ << bytes;
  ps.bytesFrom(data);

  return STATE_GOOD;
}