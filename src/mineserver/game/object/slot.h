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

#ifndef MINESERVER_GAME_OBJECT_SLOT_H
#define MINESERVER_GAME_OBJECT_SLOT_H

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
      bool m_enchantable;
      Mineserver::NBT m_enchantedData;

    public:
      Game_Object_Slot() : m_itemId(-1),m_count(0),m_damage(0),m_enchantable(false),m_enchantedData(Mineserver::NBT(Mineserver::NBT::TAG_COMPOUND, Mineserver::NBT::TAG_SHORT)) {}
      Game_Object_Slot(int16_t itemId) : m_itemId(itemId),m_count(1),m_damage(0),m_enchantable(false),m_enchantedData(Mineserver::NBT(Mineserver::NBT::TAG_COMPOUND, Mineserver::NBT::TAG_SHORT)) {}
      Game_Object_Slot(int16_t itemId, int8_t count, int16_t damage) : m_itemId(itemId),m_count(count),m_damage(damage),m_enchantable(false),m_enchantedData(Mineserver::NBT(Mineserver::NBT::TAG_COMPOUND, Mineserver::NBT::TAG_SHORT)) {}
      Game_Object_Slot(int16_t itemId, int8_t count, int16_t damage, Mineserver::NBT enchantedData) : m_itemId(itemId),m_count(count),m_damage(damage),m_enchantable(true),m_enchantedData(enchantedData) {}
      Game_Object_Slot(int16_t itemId, int8_t count, int16_t damage, bool enchantable, Mineserver::NBT enchantedData) : m_itemId(itemId),m_count(count),m_damage(damage),m_enchantable(enchantable),m_enchantedData(enchantedData) {}

      int16_t getItemId() const { return m_itemId; }
      int8_t getCount() const { return m_count; }
      int16_t getDamage() const { return m_damage; }
      int16_t getUses() const { return m_damage; }
      bool getEnchantable() const { return m_enchantable; }
      Mineserver::NBT getEnchantedData() const { return m_enchantedData; }

      void setItemId(int16_t itemId) { m_itemId = itemId; }
      void setCount(int8_t count) { m_count = count; }
      void setDamage(int16_t damage) { m_damage = damage; }
      void setUses(int16_t uses) { m_damage = uses; }
      void setEnchantable(bool enchantable) { m_enchantable = enchantable; }
      void setEnchantedData(Mineserver::NBT enchantedData) { m_enchantedData = enchantedData; }
  };
}

#endif
