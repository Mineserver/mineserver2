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

#ifndef MINESERVER_NETWORK_MESSAGE_H
#define MINESERVER_NETWORK_MESSAGE_H

#include <boost/shared_ptr.hpp>

#include <mineserver/byteorder.h>

namespace Mineserver
{
  class Network_Message
  {
  public:
    typedef boost::shared_ptr<Mineserver::Network_Message> pointer_t;

    enum messageType
    {
      MESSAGE_KEEP_ALIVE = 0x00,
      MESSAGE_LOGIN = 0x01,
      MESSAGE_HANDSHAKE = 0x02,
      MESSAGE_CHAT_MESSAGE = 0x03,
      MESSAGE_TIME_UPDATE = 0x04,
      MESSAGE_ENTITY_EQUIPMENT = 0x05,
      MESSAGE_SPAWN_POSITION = 0x06,
      MESSAGE_USE_ENTITY = 0x07,
      MESSAGE_UPDATE_HEALTH = 0x08,
      MESSAGE_RESPAWN = 0x09,
      MESSAGE_PLAYER = 0x0A,
      MESSAGE_PLAYER_POSITION = 0x0B,
      MESSAGE_PLAYER_LOOK = 0x0C,
      MESSAGE_PLAYER_POSITION_AND_LOOK = 0x0D,
      MESSAGE_PLAYER_DIGGING = 0x0E,
      MESSAGE_PLAYER_BLOCK_PLACEMENT = 0x0F,
      MESSAGE_HOLDING_CHANGE = 0x10,
      MESSAGE_USE_BED = 0x11,
      MESSAGE_ANIMATION = 0x12,
      MESSAGE_ENTITY_ACTION = 0x13,
      MESSAGE_NAMED_ENTITY_SPAWN = 0x14,
      MESSAGE_PICKUP_SPAWN = 0x15,
      MESSAGE_COLLECT_ITEM = 0x16,
      MESSAGE_ADD_OBJECT_OR_VEHICLE = 0x17,
      MESSAGE_MOB_SPAWN = 0x18,
      MESSAGE_PAINTING = 0x19,
      MESSAGE_EXPERIENCE_ORB = 0x1A,
      MESSAGE_STANCE_UPDATE = 0x1B,
      MESSAGE_ENTITY_VELOCITY = 0x1C,
      MESSAGE_DESTROY_ENTITY = 0x1D,
      MESSAGE_ENTITY = 0x1E,
      MESSAGE_ENTITY_RELATIVE_MOVE = 0x1F,
      MESSAGE_ENTITY_LOOK = 0x20,
      MESSAGE_ENTITY_LOOK_AND_RELATIVE_MOVE = 0x21,
      MESSAGE_ENTITY_TELEPORT = 0x22,
      MESSAGE_ENTITY_STATUS = 0x26,
      MESSAGE_ATTACH_ENTITY = 0x27,
      MESSAGE_ENTITY_METADATA = 0x28,
      MESSAGE_ENTITY_EFFECT = 0x29,
      MESSAGE_ENTITY_EFFECT_REMOVE = 0x2A,
      MESSAGE_EXPERIENCE = 0x2B,
      MESSAGE_PRE_CHUNK = 0x32,
      MESSAGE_MAP_CHUNK = 0x33,
      MESSAGE_MULTI_BLOCK_CHANGE = 0x34,
      MESSAGE_BLOCK_CHANGE = 0x35,
      MESSAGE_BLOCK_ACTION = 0x36,
      MESSAGE_EXPLOSION = 0x3C,
      MESSAGE_SOUND_EFFECT = 0x3D,
      MESSAGE_NEW_OR_INVALID_STATE = 0x46,
      MESSAGE_THUNDERBOLT = 0x47,
      MESSAGE_OPEN_WINDOW = 0x64,
      MESSAGE_CLOSE_WINDOW = 0x65,
      MESSAGE_WINDOW_CLICK = 0x66,
      MESSAGE_SET_SLOT = 0x67,
      MESSAGE_WINDOW_ITEMS = 0x68,
      MESSAGE_UPDATE_PROGRESS_BAR = 0x69,
      MESSAGE_TRANSACTION = 0x6A,
      MESSAGE_CREATIVE_INVENTORY_ACTION = 0x6B,
      MESSAGE_ENCHANT_ITEM = 0x6C,
      MESSAGE_UPDATE_SIGN = 0x82,
      MESSAGE_ITEM_DATA = 0x83,
      MESSAGE_INCREMENT_STATISTIC = 0xC8,
      MESSAGE_PLAYER_LIST_ITEM = 0xC9,
      MESSAGE_LIST_PING = 0xFE,
      MESSAGE_KICK = 0xFF
    } messageTypes;

  public:
    uint8_t mid;
  };
}

#endif
