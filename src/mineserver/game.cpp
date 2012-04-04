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

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <cmath>
#include <fstream>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <mineserver/localization.h>
#include <mineserver/network/client.h>
#include <mineserver/network/message/chat.h>
#include <mineserver/network/message/login.h>
#include <mineserver/network/message/handshake.h>
#include <mineserver/network/message/chunkprepare.h>
#include <mineserver/network/message/chunk.h>
#include <mineserver/network/message/spawnposition.h>
#include <mineserver/network/message/windowitems.h>
#include <mineserver/network/message/position.h>
#include <mineserver/network/message/orientation.h>
#include <mineserver/network/message/positionandorientation.h>
#include <mineserver/network/message/namedentityspawn.h>
#include <mineserver/network/message/destroyentity.h>
#include <mineserver/network/message/entityteleport.h>
#include <mineserver/network/message/entitylook.h>
#include <mineserver/network/message/entityrelativemove.h>
#include <mineserver/network/message/entityrelativemoveandlook.h>
#include <mineserver/network/message/digging.h>
#include <mineserver/network/message/blockplacement.h>
#include <mineserver/network/message/blockchange.h>
#include <mineserver/network/message/playerlistitem.h>
#include <mineserver/network/message/serverlistping.h>
#include <mineserver/network/message/kick.h>
#include <mineserver/sysconfig.h>
#include <mineserver/game.h>
#include <mineserver/game/command.h>
#include <mineserver/game/object/slot.h>

bool is_dead(Mineserver::Network_Client::pointer_t client) {
  return client->alive() == false;
}

void Mineserver::Game::run()
{
  for (clientList_t::iterator client_it=m_clients.begin();client_it!=m_clients.end();++client_it) {
    Mineserver::Network_Client::pointer_t client(*client_it);

    if (!client) {
      std::cout << "Got an invalid pointer somehow..." << std::endl;
      continue;
    }

    // 1200 in-game ticks = timed out, inactive ticks = ticks past since last keep-alive:
    if (client->inactiveTicks() > timeOutTicks) {
      std::cout << "Client timed-out." << std::endl;
      client->timedOut();
    }

    if (!client->alive()) {
      std::cout << "Found a dead client." << std::endl;

      if (m_clientMap.find(client) != m_clientMap.end()) {
        Mineserver::Game_Player::pointer_t player(m_clientMap[client]);
        int remaining = 0;
        int dbg = 0;

        std::cout << "Player " << m_clientMap[client]->getName() << " had " << m_playerMap[player].size() << " clients";
        m_playerMap[player].erase(std::remove(m_playerMap[player].begin(), m_playerMap[player].end(), client), m_playerMap[player].end());
        std::cout << ", now has " << m_playerMap[player].size() << " clients" << std::endl;

        if(m_playerMap[player].size() == 0) { // last client closed the connection
          m_players.erase(m_clientMap[client]->getName()); // drop player
          this->leavingPostWatcher(shared_from_this(), player);
        }

        m_clientMap.erase(client);
      }

      continue;
    }

    if (m_lastPlayerListItemUpdate >= playerListItemUpdateInterval)
    {
      m_lastPlayerListItemUpdate = 0;
      for (clientList_t::iterator client2_it=m_clients.begin();client2_it!=m_clients.end();++client2_it) {
        Mineserver::Network_Client::pointer_t client2(*client2_it);
        if (m_clientMap.find(client2) != m_clientMap.end()) {
          Mineserver::Game_Player::pointer_t player(m_clientMap[client2]);

          boost::shared_ptr<Mineserver::Network_Message_PlayerListItem> response = boost::make_shared<Mineserver::Network_Message_PlayerListItem>();
          response->mid = 0xC9;
          response->name = player->getName();
          response->online = true;
          response->ping = 0; // TODO: Calculate a player's ping
          client->outgoing().push_back(response);

        }
      }
    }
    else
    {
      m_lastPlayerListItemUpdate++;
    }

    std::cout << "There are " << client->incoming().size() << " messages." << std::endl;

    for (std::vector<Mineserver::Network_Message::pointer_t>::iterator message_it=client->incoming().begin();message_it!=client->incoming().end();++message_it) {
      Mineserver::Network_Message::pointer_t message = *message_it;
      m_messageWatchers[message->mid](shared_from_this(), client, message);
    }

    std::cout << "Watchers done." << std::endl;

    client->incoming().clear();

    client->run();

    client->write();
  }

  m_clients.erase(remove_if(m_clients.begin(), m_clients.end(), is_dead), m_clients.end());

  for (playerList_t::iterator player_it=m_players.begin();player_it!=m_players.end();++player_it) {
    Mineserver::Game_Player::pointer_t player(player_it->second);
    player->run();
  }
}

void Mineserver::Game::messageWatcherKeepAlive(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "KeepAlive watcher called!" << std::endl;

  client->resetInactiveTicks();
}

void Mineserver::Game::messageWatcherHandshake(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "Handshake watcher called!" << std::endl;

  boost::shared_ptr<Mineserver::Network_Message_Handshake> response = boost::make_shared<Mineserver::Network_Message_Handshake>();
  response->mid = 0x02;
  response->username = "-";
  client->outgoing().push_back(response);
}

void Mineserver::Game::messageWatcherChat(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "Chat watcher called!" << std::endl;

  const Mineserver::Network_Message_Chat* msg = reinterpret_cast<Mineserver::Network_Message_Chat*>(&(*message));

  Mineserver::Network_Client::pointer_t cclient = client;
  Mineserver::Game_Player::pointer_t player = getPlayerForClient(client);
  if(msg->message[0] == '/')
  {
    Mineserver::Command cmd(msg->message, client, player, true);
    cmd.execute(shared_from_this(),this->m_clients, client);
  }

  else
  {
    chatPostWatcher(shared_from_this(), getPlayerForClient(client), msg->message);
  }

}

void Mineserver::Game::messageWatcherLogin(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "Login watcher called!" << std::endl;

  const Mineserver::Network_Message_Login* msg = reinterpret_cast<Mineserver::Network_Message_Login*>(&(*message));

  Mineserver::World::pointer_t world = getWorld(0);

  std::cout << "Player login v." << msg->version << ": " << msg->username << std::endl;

  Mineserver::Game_Player::pointer_t player;
  if (m_players.find(msg->username) == m_players.end())
  {
    player = boost::make_shared<Mineserver::Game_Player>();
    player->setName(msg->username);
    player->setEid(getNextEid());
    player->getPosition().x = world->getSpawnPosition().x;
    player->getPosition().y = world->getSpawnPosition().y;
    player->getPosition().z = world->getSpawnPosition().z;
    player->getPosition().stance = player->getPosition().y + 1.62;
    player->getPosition().onGround = true;
    addPlayer(player);
  } else
    player = m_players[msg->username];

  associateClient(client, player);

  // FIXME: This needs to be moved somewhere else so the player doesn't hang on connect as long
  if (msg->version > PROTOCOL_VERSION)
  {
    client->Kick("Your client version is not supported by this server!");
    return; // don't allow the rest of the function to process, it can hang the client
  }
  else if (msg->version < PROTOCOL_VERSION)
  {
    client->Kick("Your client is outdated!");
    return;
  }
  
  boost::shared_ptr<Mineserver::Network_Message_Login> loginMessage = boost::make_shared<Mineserver::Network_Message_Login>();
  loginMessage->mid = 0x01;
  loginMessage->version = PROTOCOL_VERSION;
  //loginMessage->seed = 0; // flame: Changed this to 0 because I think it removes client side boimes - not 100% sure though.
  loginMessage->seed = world->getWorldSeed();
  loginMessage->mode = world->getGameMode();
  loginMessage->dimension = world->getDimension();
  loginMessage->difficulty = world->getDifficulty();
  loginMessage->worldHeight = world->getWorldHeight();
  loginMessage->levelType = "DEFAULT"; // Justasic: I think this tells the client that its level type is DEFAULT
  loginMessage->maxPlayers = 32; // this determines how many slots the tab window will have
  client->outgoing().push_back(loginMessage);

  for (int x = -5; x <= 5; ++x)
  {
    for (int z = -5; z <= 5; ++z)
    {
      boost::shared_ptr<Mineserver::Network_Message_ChunkPrepare> chunkPrepareMessage = boost::make_shared<Mineserver::Network_Message_ChunkPrepare>();
      chunkPrepareMessage->mid = 0x32;
      chunkPrepareMessage->x = x;
      chunkPrepareMessage->z = z;
      chunkPrepareMessage->mode = 1;
      client->outgoing().push_back(chunkPrepareMessage);
    }
  }

  for (int x = -5; x <= 5; ++x)
  {
    for (int z = -5; z <= 5; ++z)
    {
      boost::shared_ptr<Mineserver::Network_Message_Chunk> chunkMessage = boost::make_shared<Mineserver::Network_Message_Chunk>();
      chunkMessage->mid = 0x33;
      chunkMessage->posX = x * 16;
      chunkMessage->posY = 0;
      chunkMessage->posZ = z * 16;
      chunkMessage->sizeX = 15;
      chunkMessage->sizeY = 127;
      chunkMessage->sizeZ = 15;
      chunkMessage->chunk = world->generateChunk(x, z);
      client->outgoing().push_back(chunkMessage);
    }
  }

  boost::shared_ptr<Mineserver::Network_Message_SpawnPosition> spawnPositionMessage = boost::make_shared<Mineserver::Network_Message_SpawnPosition>();
  spawnPositionMessage->mid = 0x06;
  spawnPositionMessage->x = world->getSpawnPosition().x;
  spawnPositionMessage->y = world->getSpawnPosition().y;
  spawnPositionMessage->z = world->getSpawnPosition().z;
  client->outgoing().push_back(spawnPositionMessage);

  boost::shared_ptr<Mineserver::Network_Message_WindowItems> windowItemsMessage = boost::make_shared<Mineserver::Network_Message_WindowItems>();
  windowItemsMessage->mid = 0x68;
  windowItemsMessage->windowId = 0;
  windowItemsMessage->count = 44;
  windowItemsMessage->slots.resize(windowItemsMessage->count);
  //for (Network_Message_WindowItems::slotList_t::iterator it = windowItemsMessage->slots.begin(); it != windowItemsMessage->slots.end(); ++it) {
  //  (*it) = Game_Object_Slot(-1, 0, 0);
  //}
  //windowItemsMessage->slots[36].setItemId(278); windowItemsMessage->slots[36].setCount(1); windowItemsMessage->slots[36].setEnchantable(true);
  //windowItemsMessage->slots[37].setItemId(277); windowItemsMessage->slots[37].setCount(1); windowItemsMessage->slots[36].setEnchantable(true);
  //windowItemsMessage->slots[38].setItemId(279); windowItemsMessage->slots[38].setCount(1); windowItemsMessage->slots[36].setEnchantable(true);
  windowItemsMessage->slots[39].setItemId(1); windowItemsMessage->slots[39].setCount(64);
  windowItemsMessage->slots[40].setItemId(3); windowItemsMessage->slots[40].setCount(64);
  windowItemsMessage->slots[41].setItemId(5); windowItemsMessage->slots[41].setCount(64);
  windowItemsMessage->slots[42].setItemId(58); windowItemsMessage->slots[42].setCount(64);
  windowItemsMessage->slots[43].setItemId(54); windowItemsMessage->slots[43].setCount(64);
  windowItemsMessage->slots[44].setItemId(102); windowItemsMessage->slots[44].setCount(64);
  client->outgoing().push_back(windowItemsMessage);

  std::cout << "Spawning player at " << player->getPosition().x << "," << player->getPosition().y << "," << player->getPosition().z << std::endl;

  boost::shared_ptr<Mineserver::Network_Message_PositionAndOrientation> positionAndOrientationMessage = boost::make_shared<Mineserver::Network_Message_PositionAndOrientation>();
  positionAndOrientationMessage->mid = 0x0D;
  positionAndOrientationMessage->x = player->getPosition().x;
  positionAndOrientationMessage->y = player->getPosition().y;
  positionAndOrientationMessage->z = player->getPosition().z;
  positionAndOrientationMessage->stance = player->getPosition().stance;
  positionAndOrientationMessage->yaw = player->getPosition().yaw;
  positionAndOrientationMessage->pitch = player->getPosition().pitch;
  positionAndOrientationMessage->onGround = player->getPosition().onGround;
  client->outgoing().push_back(positionAndOrientationMessage);

  for(clientList_t::iterator it = m_clients.begin(); it != m_clients.end(); ++it)
  {
    Mineserver::Network_Client::pointer_t cclient = *it;
    boost::shared_ptr<Mineserver::Network_Message_PlayerListItem> playerListItemMessage = boost::make_shared<Mineserver::Network_Message_PlayerListItem>();
    playerListItemMessage->mid = 0xC9;
    playerListItemMessage->name = player->getName();
    playerListItemMessage->online = true;
    playerListItemMessage->ping = -1; // Note: this player shouldn't have a ping yet, so we should leave this -1
    cclient->outgoing().push_back(playerListItemMessage);

    cclient->Message("§e%s joined the game.", msg->username.c_str());
  }
}

void Mineserver::Game::messageWatcherPosition(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "Position watcher called!" << std::endl;

  const Mineserver::Network_Message_Position* msg = reinterpret_cast<Mineserver::Network_Message_Position*>(&(*message));

  if (clientIsAssociated(client)) 
  {
    Mineserver::Game_Player::pointer_t player = getPlayerForClient(client);
    Mineserver::Game_PlayerPosition position(msg->x, msg->y, msg->z, msg->stance, player->getPosition().pitch, player->getPosition().yaw, msg->onGround);
    movementPostWatcher(shared_from_this(), getPlayerForClient(client), position);

    int32_t chunkX = std::floor(player->getPosition().x);
    int32_t chunkZ = std::floor(player->getPosition().z);

    chunkX = std::floor(chunkX >> 4);
    chunkZ = std::floor(chunkZ >> 4);

    if(chunkX != oldChunkX or chunkZ != oldChunkZ)
    {
      Mineserver::World::pointer_t world = getWorld(0);

//       client->Message("You changed chunk");

      for(int32_t tempX = chunkX - 5;tempX<chunkX+5;tempX++)
      {
        for(int32_t tempZ = chunkZ - 5;tempZ<chunkZ+5;tempZ++)
        {
        boost::shared_ptr<Mineserver::Network_Message_ChunkPrepare> chunkPrepareMessage = boost::make_shared<Mineserver::Network_Message_ChunkPrepare>();
        chunkPrepareMessage->mid = 0x32;
        chunkPrepareMessage->x = tempX;
        chunkPrepareMessage->z = tempZ;
        chunkPrepareMessage->mode = 1;
        client->outgoing().push_back(chunkPrepareMessage);

        boost::shared_ptr<Mineserver::Network_Message_Chunk> chunkMessage = boost::make_shared<Mineserver::Network_Message_Chunk>();
        chunkMessage->mid = 0x33;
        chunkMessage->posX = tempX << 4;
        chunkMessage->posY = 0;
        chunkMessage->posZ = tempZ << 4;
        chunkMessage->sizeX = 15;
        chunkMessage->sizeY = 127;
        chunkMessage->sizeZ = 15;
        chunkMessage->chunk = world->generateChunk(tempX , tempZ);
        client->outgoing().push_back(chunkMessage);
        }
      }

      oldChunkX = chunkX;
      oldChunkZ = chunkZ;
    }
  }
}


void Mineserver::Game::messageWatcherOrientation(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "Orientation watcher called!" << std::endl;

  const Mineserver::Network_Message_Orientation* msg = reinterpret_cast<Mineserver::Network_Message_Orientation*>(&(*message));

  if (clientIsAssociated(client)) {
    Mineserver::Game_Player::pointer_t player = getPlayerForClient(client);
    Mineserver::Game_PlayerPosition position(player->getPosition().x, player->getPosition().y, player->getPosition().z, player->getPosition().stance, msg->pitch, msg->yaw, msg->onGround);
    movementPostWatcher(shared_from_this(), getPlayerForClient(client), position);
  }
}

void Mineserver::Game::messageWatcherPositionAndOrientation(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "PositionAndOrientation watcher called!" << std::endl;

  const Mineserver::Network_Message_PositionAndOrientation* msg = reinterpret_cast<Mineserver::Network_Message_PositionAndOrientation*>(&(*message));

  if (clientIsAssociated(client)) {

  }
}

void Mineserver::Game::messageWatcherDigging(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "Digging watcher called!" << std::endl;

  const Mineserver::Network_Message_Digging* msg = reinterpret_cast<Mineserver::Network_Message_Digging*>(&(*message));
  if (!clientIsAssociated(client)) { return; }

  // status 0x00: start digging
  // status 0x02: finish digging
  // status 0x04: drop item
  // status 0x05: shoot arrow

  if (msg->status != 0 && msg->status != 2) { return; }

  Mineserver::World::pointer_t world = getWorld(0);

  int chunk_x, chunk_z;
  chunk_x = ((msg->x) >> 4);
  chunk_z = ((msg->z) >> 4);

  if (!world->hasChunk(chunk_x, chunk_z))
  {
    std::cout << "Chunk " << chunk_x << "," << chunk_z << " not found!" << std::endl;
  }
  else
  {
    Mineserver::World_Chunk::pointer_t chunk = world->getChunk(chunk_x, chunk_z);
    Mineserver::World_ChunkPosition cPosition = Mineserver::World_ChunkPosition(msg->x & 15, msg->y, msg->z & 15);
    Mineserver::WorldBlockPosition wPosition = Mineserver::WorldBlockPosition(msg->x, msg->y, msg->z);

    uint8_t type = chunk->getBlockType(cPosition.x, cPosition.y, cPosition.z);

    if (type != 0x07) // if type is not bedrock
    {
      chunk->setBlockType(cPosition.x, cPosition.y, cPosition.z, 0);
      chunk->setBlockMeta(cPosition.x, cPosition.y, cPosition.z, 0);

      blockBreakPostWatcher(shared_from_this(), getPlayerForClient(client), world, wPosition, chunk, cPosition);
    }

  }
}

void Mineserver::Game::messageWatcherBlockPlacement(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{

  const Mineserver::Network_Message_BlockPlacement* msg = reinterpret_cast<Mineserver::Network_Message_BlockPlacement*>(&(*message));
  std::cout << "BlockPlacement watcher called! " << "Item id " << int(msg->itemId);

  if (!clientIsAssociated(client)) { return; }

  Mineserver::World::pointer_t world = game->getWorld(0);

  int32_t translatedX = msg->x;
  int32_t translatedY = msg->y;
  int32_t translatedZ = msg->z;

  switch (msg->direction)
  {
    case -1:
      // Block interaction, not placement
      break;
    case 0:
      translatedY--;
      break;
    case 1:
      translatedY++;
      break;
    case 2:
      translatedZ--;
      break;
    case 3:
      translatedZ++;
      break;
    case 4:
      translatedX--;
      break;
    case 5:
      translatedX++;
      break;
  }

  std::cout << " at {" << int(msg->x) << "," << int(msg->y) << "," << int(msg->z) <<
  "} direction " << int(msg->direction) << " -> translated to {" <<
  int(translatedX) << "," << int(translatedY) << "," << int(translatedZ) <<
  "}" << std::endl;

  int chunk_x, chunk_z;
  chunk_x = ((translatedX) >> 4);
  chunk_z = ((translatedZ) >> 4);

  if (!world->hasChunk(chunk_x, chunk_z))
  {
    std::cout << "Chunk " << chunk_x << "," << chunk_z << " not found!" << std::endl;
  }
  else
  {
    Mineserver::World_Chunk::pointer_t chunk = world->getChunk(chunk_x, chunk_z);
    Mineserver::World_ChunkPosition cPosition = Mineserver::World_ChunkPosition(translatedX & 15, translatedY, translatedZ & 15);
    Mineserver::WorldBlockPosition wPosition = Mineserver::WorldBlockPosition(translatedX, translatedY, translatedZ);

    uint8_t itemId = chunk->getBlockType(cPosition.x, cPosition.y, cPosition.z);
    uint8_t itemMeta = chunk->getBlockMeta(cPosition.x, cPosition.y, cPosition.z);

    if (msg->y != -1 && msg->direction != -1 && msg->itemId != -1)
    {
      // TODO: We will check if there's air here or not, but later we need to move this into blockPlacePreWatcher
      if (itemId == 0)
      {
        chunk->setBlockType(cPosition.x, cPosition.y, cPosition.z, msg->itemId);
        chunk->setBlockMeta(cPosition.x, cPosition.y, cPosition.z, msg->damage);

        blockPlacePostWatcher(shared_from_this(), getPlayerForClient(client), world, wPosition, chunk, cPosition, msg->itemId, msg->damage);
      }
      else
      {
        std::cout << "Player tried to place a block where one already exists." << std::endl;
      }
    }
    else if (msg->x == -1 && msg->y == -1 && msg->z == -1 && msg->direction == -1)
    {
      // TODO: Do pre/post block interaction
    }
    else
    {
      std::cout << "BlockPlacement watcher is doing something funny." << std::endl;
    }

  }
}

void Mineserver::Game::messageWatcherBlockChange(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "BlockChange watcher called!" << std::endl;
  const Mineserver::Network_Message_BlockChange* msg = reinterpret_cast<Mineserver::Network_Message_BlockChange*>(&(*message));

  Mineserver::World::pointer_t world = game->getWorld(0);

  int chunk_x, chunk_z;
  chunk_x = ((msg->x) >> 4);
  chunk_z = ((msg->z) >> 4);

  if (!world->hasChunk(chunk_x, chunk_z))
  {
    std::cout << "Chunk " << chunk_x << "," << chunk_z << " not found!" << std::endl;
  }
  else
  {
    Mineserver::World_Chunk::pointer_t chunk = world->getChunk(chunk_x, chunk_z);
    Mineserver::World_ChunkPosition cPosition = Mineserver::World_ChunkPosition(msg->x & 15, msg->y, msg->z & 15);
    Mineserver::WorldBlockPosition wPosition = Mineserver::WorldBlockPosition(msg->x, msg->y, msg->z);

    // TODO: What is this watcher supposed to do? Minecraft doesn't seem to send this packet to us,
    //       even though the http://wiki.vg/Protocol says it can go both ways... :S
  }
}

void Mineserver::Game::messageWatcherServerListPing(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message)
{
  std::cout << "ServerListPing watcher called!" << std::endl;

  std::stringstream reason;
  reason << "Mineserver " << VERSION_SIMPLE << "§" << game->countPlayers() << "§" << 32; // TODO: Get max players

  client->Kick(reason.str());
}

bool Mineserver::Game::chatPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, std::string message)
{
  boost::shared_ptr<Mineserver::Network_Message_Chat> chatMessage = boost::make_shared<Mineserver::Network_Message_Chat>();
  chatMessage->mid = 0x03;
  chatMessage->message = "<" + player->getName() + "> " + message;

  for (clientList_t::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
    (*it)->outgoing().push_back(chatMessage);
  }

  return true;
}

// START TODO:
// This entire function needs rewriting.
//
bool Mineserver::Game::movementPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::Game_PlayerPosition position)
{
  std::cout << "movementPostWatcher called!" << std::endl;

  Mineserver::Game_PlayerPosition oldPos = player->getPosition();
  player->setPosition(position);

  boost::shared_ptr<Mineserver::Network_Message> player_move;
  double dX = (position.x - oldPos.x);
  double dY = (position.y - oldPos.y);
  double dZ = (position.z - oldPos.z);
  if( dX > 4 || dX < -4 || dY > 4 || dY < -4 || dZ > 4 || dZ < -4 )
  {
    // Entity Teleport
    boost::shared_ptr<Mineserver::Network_Message_EntityTeleport> tmp = boost::make_shared<Mineserver::Network_Message_EntityTeleport>();
    tmp->mid = 0x22;
    tmp->entityId = player->getEid();
    tmp->x      = static_cast<int32_t>((position.x * 32));
    tmp->y      = static_cast<int32_t>((position.y * 32));
    tmp->z      = static_cast<int32_t>((position.z * 32));
    tmp->pitch  = static_cast<int8_t>((position.pitch / 360 * 256));
    tmp->yaw    = static_cast<int8_t>((position.yaw / 360 * 256));
    player_move = tmp;
  }
  else if ((oldPos.yaw != position.yaw || oldPos.pitch != position.pitch)
           && (oldPos.x == position.x && oldPos.y == position.y && oldPos.z == position.z))
  {
    // Entity Look
    boost::shared_ptr<Mineserver::Network_Message_EntityLook> tmp = boost::make_shared<Mineserver::Network_Message_EntityLook>();
    tmp->mid = 0x20;
    tmp->entityId = player->getEid();
    tmp->yaw    = static_cast<int8_t>((position.yaw / 360 * 256));
    tmp->pitch  = static_cast<int8_t>((position.pitch / 360 * 256));
    player_move = tmp;
  }
  else if ((oldPos.yaw == position.yaw && oldPos.pitch == position.pitch)
           && (oldPos.x != position.x || oldPos.y != position.y || oldPos.z != position.z))
  {
    // Entity Relative Move
    boost::shared_ptr<Mineserver::Network_Message_EntityRelativeMove> tmp = boost::make_shared<Mineserver::Network_Message_EntityRelativeMove>();
    tmp->mid = 0x1F;
    tmp->entityId = player->getEid();
    tmp->x      = static_cast<int8_t>((dX * 32));
    tmp->y      = static_cast<int8_t>((dY * 32));
    tmp->z      = static_cast<int8_t>((dZ * 32));
    player_move = tmp;
  }
  else
  {
    // Entity Relative Move & Look
    boost::shared_ptr<Mineserver::Network_Message_EntityRelativeMoveAndLook> tmp = boost::make_shared<Mineserver::Network_Message_EntityRelativeMoveAndLook>();
    tmp->mid = 0x21;
    tmp->entityId = player->getEid();
    tmp->x      = static_cast<int8_t>((dX * 32));
    tmp->y      = static_cast<int8_t>((dY * 32));
    tmp->z      = static_cast<int8_t>((dZ * 32));
    tmp->yaw    = static_cast<int8_t>((position.yaw / 360 * 256));
    tmp->pitch  = static_cast<int8_t>((position.pitch / 360 * 256));
    player_move = tmp;
  }

  uint8_t in_distance = (16 * 3);    // 160 => 10 chunks
  uint8_t out_distance = (16 * 5);   // 192 => 12 chunks

  // check if we are within range of another player now

  double delta_x, delta_y, old_distance, new_distance;

  entityIdSet_t others = m_playerInRange[player];
  clientList_t other_clients;
  clientList_t my_clients = getClientsForPlayer(player);

  for (playerList_t::iterator player_it=m_players.begin();player_it!=m_players.end();++player_it) {
    Mineserver::Game_Player::pointer_t other(player_it->second);
    if(other == player) { continue; }
    other_clients = getClientsForPlayer(other);

    // calc new distance
    delta_x = position.x - other->getPosition().x;
    delta_y = position.y - other->getPosition().y;
    new_distance = sqrt(delta_x*delta_x+delta_y*delta_y);
    std::cout << " [" << other->getEid() << "] in range of [" << player->getEid() << "]?" << std::endl;
    std::cout << " [" << other->getEid() << "] distance to [" << player->getEid() << "]: " << new_distance << std::endl;
    if(others.count(other->getEid()) >= 1) {  // we are in range of this one
      if(new_distance > out_distance) { // but now we are out
        // send destroy entity
        boost::shared_ptr<Mineserver::Network_Message_DestroyEntity> destroyEntity = boost::make_shared<Mineserver::Network_Message_DestroyEntity>();
        destroyEntity->mid = 0x1D;
        destroyEntity->entityId = player->getEid();
        for(clientList_t::iterator it=other_clients.begin();it != other_clients.end(); it++) {
          std::cout << " [" << other->getEid() << "] << destroy entity #" << player->getEid() << std::endl;
          (*it)->outgoing().push_back(destroyEntity);
        }
        // destroy entity on both sides!
        destroyEntity = boost::make_shared<Mineserver::Network_Message_DestroyEntity>();
        destroyEntity->mid = 0x1D;
        destroyEntity->entityId = other->getEid();
        for(clientList_t::iterator it=my_clients.begin();it!=my_clients.end();it++) {
          std::cout << " [" << player->getEid() << "] << destroy entity #" << other->getEid() << std::endl;
          (*it)->outgoing().push_back(destroyEntity);
        }
        // remove player from set
        others.erase(other->getEid());
      } else { // still range
        // update entity position => send
        for(clientList_t::iterator it=other_clients.begin();it != other_clients.end(); it++) {
          (*it)->outgoing().push_back(player_move);
        }
      }
    } else { // player is NOT in range of this one
      if(new_distance < in_distance) { // but we just entered the range
        boost::shared_ptr<Mineserver::Network_Message_NamedEntitySpawn> spawnEntity = boost::make_shared<Mineserver::Network_Message_NamedEntitySpawn>();
        spawnEntity->mid = 0x14;
        spawnEntity->entityId = player->getEid();
        spawnEntity->name     = player->getName();
	spawnEntity->x        = static_cast<int32_t>(oldPos.x * 32);
	spawnEntity->y        = static_cast<int32_t>(oldPos.y * 32);
	spawnEntity->z        = static_cast<int32_t>(oldPos.z * 32);
	spawnEntity->rotation = static_cast<int8_t>((oldPos.yaw / 360 * 256));
	spawnEntity->pitch    = static_cast<int8_t>((oldPos.pitch / 360 * 256));
        spawnEntity->currentItem = 0;
        for(clientList_t::iterator it=other_clients.begin();it != other_clients.end(); it++) {
          std::cout << " [" << other->getEid() << "] << spawn entity #" << player->getEid() << std::endl;
          (*it)->outgoing().push_back(spawnEntity);
        }
        spawnEntity = boost::make_shared<Mineserver::Network_Message_NamedEntitySpawn>();
        spawnEntity->mid = 0x14;
        spawnEntity->entityId = other->getEid();
        spawnEntity->name     = other->getName();
	spawnEntity->x        = static_cast<int32_t>(other->getPosition().x * 32);
	spawnEntity->y        = static_cast<int32_t>(other->getPosition().y * 32);
	spawnEntity->z        = static_cast<int32_t>(other->getPosition().z * 32);
	spawnEntity->rotation = static_cast<int8_t>(other->getPosition().yaw / 360 * 256);
	spawnEntity->pitch    = static_cast<int8_t>(other->getPosition().pitch / 360 * 256);
        spawnEntity->currentItem = 0;
        for(clientList_t::iterator it=my_clients.begin();it != my_clients.end(); it++) {
          std::cout << " [" << player->getEid() << "] << spawn entity #" << other->getEid() << std::endl;
          (*it)->outgoing().push_back(spawnEntity);
        }
        others.insert(other->getEid());
        m_playerInRange[other].insert(player->getEid());
      }
    }
  }
  m_playerInRange[player] = others;
  return true;
}
// END TODO

bool Mineserver::Game::blockBreakPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::World::pointer_t world, Mineserver::WorldBlockPosition wPosition, Mineserver::World_Chunk::pointer_t chunk, Mineserver::World_ChunkPosition cPosition)
{
  std::cout << "blockBreakPostWatcher called!" << std::endl;

  boost::shared_ptr<Mineserver::Network_Message_BlockChange> blockChangeMessage = boost::make_shared<Mineserver::Network_Message_BlockChange>();
  blockChangeMessage->mid = 0x35;
  blockChangeMessage->x = wPosition.x;
  blockChangeMessage->y = wPosition.y;
  blockChangeMessage->z = wPosition.z;
  blockChangeMessage->type = 0;
  blockChangeMessage->meta = 0;

  for (clientList_t::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
    (*it)->outgoing().push_back(blockChangeMessage);
  }

  return true;
}

bool Mineserver::Game::blockPlacePostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::World::pointer_t world, Mineserver::WorldBlockPosition wPosition, Mineserver::World_Chunk::pointer_t chunk, Mineserver::World_ChunkPosition cPosition, uint8_t type, uint8_t meta)
{
  std::cout << "blockPlacePostWatcher called!" << std::endl;

  boost::shared_ptr<Mineserver::Network_Message_BlockChange> blockChangeMessage = boost::make_shared<Mineserver::Network_Message_BlockChange>();
  blockChangeMessage->mid = 0x35;
  blockChangeMessage->x = wPosition.x;
  blockChangeMessage->y = wPosition.y;
  blockChangeMessage->z = wPosition.z;
  blockChangeMessage->type = type;
  blockChangeMessage->meta = meta;

  for (clientList_t::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
    (*it)->outgoing().push_back(blockChangeMessage);
  }

  return true;
}

void Mineserver::Game::leavingPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player)
{
  std::cout << "leavingPostWatcher called! Player: " << player->getName() << std::endl;

  for(clientList_t::iterator it = m_clients.begin(); it != m_clients.end(); ++it)
  {
    Mineserver::Network_Client::pointer_t cclient = *it;
    boost::shared_ptr<Mineserver::Network_Message_PlayerListItem> playerListItemMessage = boost::make_shared<Mineserver::Network_Message_PlayerListItem>();
    playerListItemMessage->mid = 0xC9;
    playerListItemMessage->name = player->getName();
    playerListItemMessage->online = false;
    playerListItemMessage->ping = -1;
    cclient->outgoing().push_back(playerListItemMessage);

    cclient->Message("§e%s left the game.", player->getName().c_str());
  }

  clientList_t other_clients;
  for(playerList_t::iterator player_it=m_players.begin();player_it!=m_players.end();++player_it) {
    Mineserver::Game_Player::pointer_t other(player_it->second);
    if(other == player) {
      continue;
    }
    if(m_playerInRange[player].count(other->getEid()) < 1) {  // we are not in range of this one
      continue;
    }

    // send destroy entity
    boost::shared_ptr<Mineserver::Network_Message_DestroyEntity> destroyEntity = boost::make_shared<Mineserver::Network_Message_DestroyEntity>();
    destroyEntity->mid = 0x1D;
    destroyEntity->entityId = player->getEid();
    other_clients = getClientsForPlayer(other);
    for(clientList_t::iterator it=other_clients.begin();it != other_clients.end(); it++) {
      std::cout << " [" << other->getEid() << "] << destroy entity #" <<  player->getEid() << std::endl;
      (*it)->outgoing().push_back(destroyEntity);
    }
  }
}
