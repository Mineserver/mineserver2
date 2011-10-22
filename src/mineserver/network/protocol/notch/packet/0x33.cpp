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

#include <mineserver/byteorder.h>
#include <mineserver/network/packet.h>
#include <mineserver/network/protocol/notch/packetstream.h>
#include <mineserver/network/protocol/notch/packet.h>
#include <mineserver/network/protocol/notch/packet/0x33.h>

void Mineserver::Network_Protocol_Notch_Packet_0x33::read(packet_stream_t& ps)
{
  ps >> pid >> posX >> posY >> posZ >> sizeX >> sizeY >> sizeZ >> bytes;
  data.reserve(bytes);
  ps.bytesTo(reinterpret_cast<uint8_t*>(&(data[0])), bytes);
  ps.remove();
}

void Mineserver::Network_Protocol_Notch_Packet_0x33::write(packet_stream_t& ps)
{
  ps << pid << posX << posY << posZ << sizeX << sizeY << sizeZ << bytes;
  ps.bytesFrom(reinterpret_cast<uint8_t*>(&(data[0])), bytes);
}