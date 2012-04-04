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

#include <utility>

#include <mineserver/byteorder.h>
#include <mineserver/nbt.h>
#include <mineserver/network/message/windowitems.h>
#include <mineserver/network/protocol/notch/packet.h>
#include <mineserver/network/protocol/notch/packet/0x68.h>

int Mineserver::Network_Protocol_Notch_Packet_0x68::_read(Mineserver::Network_Protocol_Notch_PacketStream& ps, Mineserver::Network_Message** message)
{
  Mineserver::Network_Message_WindowItems* msg = new Mineserver::Network_Message_WindowItems;
  *message = msg;

  ps >> msg->mid >> msg->windowId >> msg->count;

  int16_t itemId, uses;
  int8_t count;
  int16_t enchantedSize = 0;
  Mineserver::NBT enchantedData = Mineserver::NBT(Mineserver::NBT::TAG_COMPOUND, Mineserver::NBT::TAG_SHORT);

  for (int16_t i=0;i<count;++i) {
    itemId = uses = count = 0;

    ps >> itemId;

    if (itemId != -1) {
      ps >> count >> uses;
      // TODO: Parse enchanted data, need to know if itemId is enchantable or not first.
    }

    msg->slots.push_back(Game_Object_Slot(itemId, uses, count, (enchantedSize > 0), enchantedData));
  }

  return STATE_GOOD;
}

int Mineserver::Network_Protocol_Notch_Packet_0x68::_write(Mineserver::Network_Protocol_Notch_PacketStream& ps, const Mineserver::Network_Message& message)
{
  const Mineserver::Network_Message_WindowItems* msg = static_cast<const Mineserver::Network_Message_WindowItems*>(&message);

  ps << msg->mid << msg->windowId << msg->count;

  for (Network_Message_WindowItems::slotList_t::const_iterator it = msg->slots.begin(); it != msg->slots.end(); ++it) {
    ps << it->getItemId();

    if (it->getItemId() != -1) {
      ps << it->getCount() << it->getDamage();

      if (it->getEnchantable()) {
        std::vector<uint8_t>* data = it->getEnchantedData().GetByteArray();
        ps << static_cast<int16_t>(data->size());
        ps.bytesFrom(*data);
      }
    }
  }

  return STATE_GOOD;
}
