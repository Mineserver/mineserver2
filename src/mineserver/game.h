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

#ifndef MINESERVER_GAME_H
#define MINESERVER_GAME_H

#include <map>
#include <vector>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/signals2.hpp>
#include <boost/tuple/tuple.hpp>

#include <mineserver/game/player.h>
#include <mineserver/world.h>
#include <mineserver/world/chunk.h>
#include <mineserver/network/message.h>
#include <mineserver/network/client.h>

namespace Mineserver
{
  class Game : public boost::enable_shared_from_this<Mineserver::Game>
  {
  public:
    typedef boost::shared_ptr<Mineserver::Game> pointer_t;
    typedef std::map<std::string,Mineserver::Game_Player::pointer_t> playerList_t;
    typedef std::vector<Mineserver::Network_Client::pointer_t> clientList_t;
    typedef std::map<Mineserver::Network_Client::pointer_t,Mineserver::Game_Player::pointer_t> clientMap_t;
    typedef std::map<int,Mineserver::World::pointer_t> worldList_t;
    typedef boost::signals2::signal<void (Mineserver::Game::pointer_t, Mineserver::Network_Client::pointer_t, Mineserver::Network_Message::pointer_t message)> messageWatcher_t;
    typedef boost::signals2::signal<bool (Mineserver::Game::pointer_t, Mineserver::Game_Player::pointer_t, Mineserver::Game_PlayerPosition position)> movementPositionWatcher_t;
    typedef boost::signals2::signal<bool (Mineserver::Game::pointer_t, Mineserver::Game_Player::pointer_t, Mineserver::Game_PlayerPosition position)> movementOrientationWatcher_t;
    typedef boost::signals2::signal<bool (Mineserver::Game::pointer_t, Mineserver::Game_Player::pointer_t, Mineserver::World::pointer_t, Mineserver::World_Chunk::pointer_t, Mineserver::World_ChunkPosition position)> blockBreakWatcher_t;
    typedef boost::signals2::signal<bool (Mineserver::Game::pointer_t, Mineserver::Game_Player::pointer_t, Mineserver::World::pointer_t, Mineserver::World_Chunk::pointer_t, Mineserver::World_ChunkPosition position, uint8_t type, uint8_t meta)> blockPlaceWatcher_t;

    static const int timeOutTicks = 1200;
    enum {
      chatSelf, chatNearby, chatWorld, chatGlobal
    } messageTypes;

  private:
    int32_t m_nextEid;
    playerList_t m_players;
    clientList_t m_clients;
    clientMap_t m_clientMap;
    worldList_t m_worlds;
    messageWatcher_t m_messageWatchers[256];
    movementPositionWatcher_t m_movementPositionPreWatcher;
    movementPositionWatcher_t m_movementPositionPostWatcher;
    movementOrientationWatcher_t m_movementOrientationPreWatcher;
    movementOrientationWatcher_t m_movementOrientationPostWatcher;
    blockBreakWatcher_t m_blockBreakPreWatcher;
    blockBreakWatcher_t m_blockBreakPostWatcher;
    blockPlaceWatcher_t m_blockPlacePreWatcher;
    blockPlaceWatcher_t m_blockPlacePostWatcher;

  public:
    void run();
		void chat(Mineserver::Network_Client::pointer_t client, std::string message);

    Game()
    {
      setWorld(0, boost::make_shared<Mineserver::World>());

      m_nextEid = 0;

      m_messageWatchers[0x0B].connect(boost::bind(&Mineserver::Game::messageWatcherPosition, this, _1, _2, _3));
      m_messageWatchers[0x0C].connect(boost::bind(&Mineserver::Game::messageWatcherOrientation, this, _1, _2, _3));
      m_messageWatchers[0x0D].connect(boost::bind(&Mineserver::Game::messageWatcherPositionAndOrientation, this, _1, _2, _3));
      m_movementPositionPostWatcher.connect(boost::bind(&Mineserver::Game::movementPositionPostWatcher, this, _1, _2, _3));
      m_movementOrientationPostWatcher.connect(boost::bind(&Mineserver::Game::movementOrientationPostWatcher, this, _1, _2, _3));
      m_blockBreakPostWatcher.connect(boost::bind(&Mineserver::Game::blockBreakPostWatcher, this, _1, _2, _3, _4, _5));
      m_blockPlacePostWatcher.connect(boost::bind(&Mineserver::Game::blockPlacePostWatcher, this, _1, _2, _3, _4, _5, _6, _7));
    }

    int32_t getNextEid() { return m_nextEid++; }

    void messageWatcherPosition(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherOrientation(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherPositionAndOrientation(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);

    bool movementPositionPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::Game_PlayerPosition position);
    bool movementOrientationPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::Game_PlayerPosition position);
    bool blockBreakPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::World::pointer_t world, Mineserver::World_Chunk::pointer_t chunk, Mineserver::World_ChunkPosition position);
    bool blockPlacePostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::World::pointer_t world, Mineserver::World_Chunk::pointer_t chunk, Mineserver::World_ChunkPosition position, uint8_t type, uint8_t meta);

    boost::signals2::connection addMessageWatcher(uint8_t messageId, const messageWatcher_t::slot_type& slot)
    {
      return m_messageWatchers[messageId].connect(slot);
    }

    boost::signals2::connection addBlockBreakPreWatcher(const blockBreakWatcher_t::slot_type& slot)
    {
      return m_blockBreakPreWatcher.connect(slot);
    }

    boost::signals2::connection addBlockBreakPostWatcher(const blockBreakWatcher_t::slot_type& slot)
    {
      return m_blockBreakPostWatcher.connect(slot);
    }

    boost::signals2::connection addBlockPlacePreWatcher(const blockPlaceWatcher_t::slot_type& slot)
    {
      return m_blockPlacePreWatcher.connect(slot);
    }

    boost::signals2::connection addBlockPlacePostWatcher(const blockPlaceWatcher_t::slot_type& slot)
    {
      return m_blockPlacePostWatcher.connect(slot);
    }

    void addPlayer(Mineserver::Game_Player::pointer_t player)
    {
      m_players[player->getName()] = player;
    }

    bool hasPlayer(const std::string& name)
    {
      return (m_players.find(name) != m_players.end());
    }

    Mineserver::Game_Player::pointer_t getPlayer(const std::string& name)
    {
      return m_players[name];
    }

    void addClient(Mineserver::Network_Client::pointer_t client)
    {
      m_clients.push_back(client);
    }

    void associateClient(Mineserver::Network_Client::pointer_t client, Mineserver::Game_Player::pointer_t player)
    {
      m_clientMap[client] = player;
    }

    bool clientIsAssociated(Mineserver::Network_Client::pointer_t client)
    {
      return (m_clientMap.find(client) != m_clientMap.end());
    }

    Mineserver::Game_Player::pointer_t getPlayerForClient(Mineserver::Network_Client::pointer_t client)
    {
      return m_clientMap[client];
    }

    void setWorld(int n, Mineserver::World::pointer_t world)
    {
			m_worlds[n] = world;
    }

    bool hasWorld(int n)
    {
			return (m_worlds.find(n) == m_worlds.end());
    }

    Mineserver::World::pointer_t getWorld(int n)
    {
      return m_worlds[n];
    }
  };
}

#endif