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

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <mineserver/game.h>
#include <mineserver/network/client.h>
#include <mineserver/network/message.h>
#include <mineserver/network/message/login.h>
#include <mineserver/network/message/kick.h>
#include <mineserver/network/message/chunkprepare.h>
#include <mineserver/network/message/chunk.h>
#include <mineserver/network/message/spawnposition.h>
#include <mineserver/network/message/windowitems.h>
#include <mineserver/network/message/positionlook.h>

#include <mineserver/watcher/login.h>

void Mineserver::Watcher_Login::operator()(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message) const
{
  std::cout << "Login watcher called!" << std::endl;
  const Mineserver::Network_Message_Login* msg = reinterpret_cast<Mineserver::Network_Message_Login*>(&(*message));

  Mineserver::Game_Player::pointer_t player(new Mineserver::Game_Player);
  player->setName(msg->username);

  std::cout << "Player login v." << msg->version << ": " << msg->username << std::endl;

  game->addPlayer(player);
  game->associateClient(client, player);

  Mineserver::World::pointer_t world = game->getWorld(0);

  boost::shared_ptr<Mineserver::Network_Message_Login> loginMessage = boost::make_shared<Mineserver::Network_Message_Login>();
  loginMessage->mid = 0x01;
  loginMessage->version = 22;
  loginMessage->seed = world->getWorldSeed();
  loginMessage->mode = world->getGameMode();
  loginMessage->dimension = world->getDimension();
  loginMessage->difficulty = world->getDifficulty();
  loginMessage->worldHeight = world->getWorldHeight();
  loginMessage->maxPlayers = 32; // this determines how many slots the tab window will have
  client->outgoing().push_back(loginMessage);

  for (int x = -5; x <= 5; ++x) {
    for (int z = -5; z <= 5; ++z) {
      boost::shared_ptr<Mineserver::Network_Message_ChunkPrepare> chunkPrepareMessage = boost::make_shared<Mineserver::Network_Message_ChunkPrepare>();
      chunkPrepareMessage->mid = 0x32;
      chunkPrepareMessage->x = x;
      chunkPrepareMessage->z = z;
      chunkPrepareMessage->mode = 1;
      client->outgoing().push_back(chunkPrepareMessage);
    }
  }

  for (int x = -5; x <= 5; ++x) {
    for (int z = -5; z <= 5; ++z) {
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
  spawnPositionMessage->x = world->getSpawnPosition().x();
  spawnPositionMessage->y = world->getSpawnPosition().y();
  spawnPositionMessage->z = world->getSpawnPosition().z();
  client->outgoing().push_back(spawnPositionMessage);

  boost::shared_ptr<Mineserver::Network_Message_WindowItems> windowItemsMessage = boost::make_shared<Mineserver::Network_Message_WindowItems>();
  windowItemsMessage->mid = 0x68;
  windowItemsMessage->windowId = -1;
  windowItemsMessage->count = 0;
  client->outgoing().push_back(windowItemsMessage);

  boost::shared_ptr<Mineserver::Network_Message_PositionLook> positionLookMessage = boost::make_shared<Mineserver::Network_Message_PositionLook>();
  positionLookMessage->mid = 0x0D;
  positionLookMessage->x = world->getSpawnPosition().x();
  positionLookMessage->y = world->getSpawnPosition().y() + 1;
  positionLookMessage->z = world->getSpawnPosition().z();
  positionLookMessage->stance = positionLookMessage->y + 1.620000005L;
  positionLookMessage->yaw = 0;
  positionLookMessage->pitch = 0;
  positionLookMessage->onGround = true;
  client->outgoing().push_back(positionLookMessage);
}

