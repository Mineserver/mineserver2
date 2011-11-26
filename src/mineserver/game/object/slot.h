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

#ifndef MINESERVER_GAME_OBJECT_SLOT_H
#define MINESERVER_GAME_OBJECT_SLOT_H

#include <vector>

#include <mineserver/byteorder.h>
#include <mineserver/nbt.h>

namespace Mineserver
{
  struct Game_Object_Slot
  {
    private:
      int16_t m_itemId;
      int8_t m_count;
      int16_t m_damage;
      bool m_enchanted;
      Mineserver::NBT m_enchantedData;

    public:
      Game_Object_Slot(int16_t itemId = 0, int8_t count = 0, int16_t damage = 0) : m_itemId(itemId),m_count(count),m_damage(damage),m_enchanted(false),m_enchantedData(Mineserver::NBT(Mineserver::NBT::TAG_COMPOUND, Mineserver::NBT::TAG_SHORT)) {}

      int16_t getItemId() { return m_itemId; }
      int8_t getCount() { return m_count; }
      int16_t getDamage() { return m_damage; }
      int16_t getUses() { return m_damage; }
      bool getEnchanted() { return m_enchanted; }
      Mineserver::NBT getEnchantedData() { return m_enchantedData; }

      void setItemId(int16_t itemId) { m_itemId = itemId; }
      void setCount(int8_t count) { m_count = count; }
      void setDamage(int16_t damage) { m_damage = damage; }
      void setUses(int16_t uses) { m_damage = uses; }
      void setEnchanted(bool enchanted) { m_enchanted = enchanted; }
      void setEnchantedData(Mineserver::NBT enchantedData) { m_enchantedData = enchantedData; }
  };
}

#endif