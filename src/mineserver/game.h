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
#include <set>

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
    typedef std::vector<Mineserver::Network_Client::pointer_t> clientList_t;
    typedef std::map<std::string,Mineserver::Game_Player::pointer_t> playerList_t;
    typedef std::map<Mineserver::Network_Client::pointer_t,Mineserver::Game_Player::pointer_t> clientMap_t;
    typedef std::map<int,Mineserver::World::pointer_t> worldList_t; 
    typedef std::set<Mineserver::Game_Player::pointer_t> playerSet_t;
    typedef std::set<uint32_t> entityIdSet_t;
    typedef std::map<Mineserver::Game_Player::pointer_t,clientList_t> playerMap_t;
    typedef std::map<Mineserver::Game_Player::pointer_t,entityIdSet_t > playerSetMap_t; // this name sucks! 
    typedef boost::signals2::signal<void (Mineserver::Game::pointer_t, Mineserver::Network_Client::pointer_t, Mineserver::Network_Message::pointer_t message)> messageWatcher_t;
    typedef boost::signals2::signal<bool (Mineserver::Game::pointer_t, Mineserver::Game_Player::pointer_t, Mineserver::Game_PlayerPosition position)> movementWatcher_t;
    typedef boost::signals2::signal<bool (Mineserver::Game::pointer_t, Mineserver::Game_Player::pointer_t, Mineserver::World::pointer_t, Mineserver::WorldBlockPosition wPosition, Mineserver::World_Chunk::pointer_t, Mineserver::World_ChunkPosition cPosition)> blockBreakWatcher_t;
    typedef boost::signals2::signal<bool (Mineserver::Game::pointer_t, Mineserver::Game_Player::pointer_t, Mineserver::World::pointer_t, Mineserver::WorldBlockPosition wPosition, Mineserver::World_Chunk::pointer_t, Mineserver::World_ChunkPosition cPosition, uint8_t type, uint8_t meta)> blockPlaceWatcher_t;

    static const uint32_t timeOutTicks = 1200;
    static const uint32_t playerListItemUpdateInterval = 20;
    enum {
      chatSelf, chatNearby, chatWorld, chatGlobal
    } messageTypes;

  private:
    int32_t m_nextEid;
    playerList_t m_players;
    clientList_t m_clients;
    playerMap_t m_playerMap;
    clientMap_t m_clientMap;
    worldList_t m_worlds;
    messageWatcher_t m_messageWatchers[256];
    movementWatcher_t m_movementPreWatcher;
    movementWatcher_t m_movementPostWatcher;
    blockBreakWatcher_t m_blockBreakPreWatcher;
    blockBreakWatcher_t m_blockBreakPostWatcher;
    blockPlaceWatcher_t m_blockPlacePreWatcher;
    blockPlaceWatcher_t m_blockPlacePostWatcher;
    playerSetMap_t  m_playerInRange;
    uint32_t m_lastPlayerListItemUpdate;

  public:
    void run();
		void chat(Mineserver::Network_Client::pointer_t client, std::string message);

    Game() : m_nextEid(0) {}

    int32_t getNextEid() { return m_nextEid++; }

    void messageWatcherKeepAlive(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherLogin(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherHandshake(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherChat(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherPosition(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherOrientation(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherPositionAndOrientation(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherDigging(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherBlockPlacement(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherBlockChange(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);
    void messageWatcherServerListPing(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message);

    bool chatPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, std::string message);
    bool movementPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::Game_PlayerPosition position);
    bool blockBreakPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::World::pointer_t world, Mineserver::WorldBlockPosition wPosition, Mineserver::World_Chunk::pointer_t chunk, Mineserver::World_ChunkPosition cPosition);
    bool blockPlacePostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player, Mineserver::World::pointer_t world, Mineserver::WorldBlockPosition wPosition, Mineserver::World_Chunk::pointer_t chunk, Mineserver::World_ChunkPosition cPosition, uint8_t type, uint8_t meta);
    void leavingPostWatcher(Mineserver::Game::pointer_t game, Mineserver::Game_Player::pointer_t player);

    boost::signals2::connection addMessageWatcher(uint8_t messageId, const messageWatcher_t::slot_type& slot)
    {
      return m_messageWatchers[messageId].connect(slot);
    }

    boost::signals2::connection addMovementPreWatcher(const movementWatcher_t::slot_type& slot)
    {
      return m_movementPreWatcher.connect(slot);
    }

    boost::signals2::connection addMovementPostWatcher(const movementWatcher_t::slot_type& slot)
    {
      return m_movementPostWatcher.connect(slot);
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

    uint32_t countPlayers() 
    {
        return m_players.size();
    }

    Mineserver::Game_Player::pointer_t getPlayer(const std::string& name)
    {
      return m_players[name];
    }

    Mineserver::Game::clientList_t& getClientsForPlayer(Mineserver::Game_Player::pointer_t player)
    {
      return m_playerMap[player];
    }

    void addClient(Mineserver::Network_Client::pointer_t client)
    {
      m_clients.push_back(client);
    }

    void associateClient(Mineserver::Network_Client::pointer_t client, Mineserver::Game_Player::pointer_t player)
    {
      m_clientMap[client] = player;
      m_playerMap[player].push_back(client);
    }

    bool clientIsAssociated(Mineserver::Network_Client::pointer_t client)
    {
      return (m_clientMap.find(client) != m_clientMap.end());
    }

    Mineserver::Game_Player::pointer_t getPlayerForClient(const Mineserver::Network_Client::pointer_t& client)
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
