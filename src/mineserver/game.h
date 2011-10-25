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

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/signals2.hpp>

#include <mineserver/game/player.h>
#include <mineserver/network/message.h>
#include <mineserver/network/client.h>

namespace Mineserver
{
  class Game : public boost::enable_shared_from_this<Mineserver::Game>
  {
  public:
    typedef boost::shared_ptr<Mineserver::Game> pointer_t;
    typedef boost::signals2::signal<void (Mineserver::Game&, Mineserver::Network_Client&, Mineserver::Network_Message&)> messageWatcher_t;
    typedef messageWatcher_t::slot_type messageWatcherSlot_t;

  private:
    std::vector<Mineserver::Game_Player::pointer_t> m_players;
    std::vector<Mineserver::Network_Client::pointer_t> m_clients;
    std::map<Mineserver::Network_Client::pointer_t,Mineserver::Game_Player::pointer_t> m_clientMap;
    messageWatcher_t m_messageWatchers[256];

  public:
    void run();

    boost::signals2::connection addWatcher(uint8_t messageId, const messageWatcherSlot_t& slot)
    {
      return m_messageWatchers[messageId].connect(slot);
    }

    void addClient(Mineserver::Network_Client::pointer_t client)
    {
      m_clients.push_back(client);
    }
  };
}

#endif
