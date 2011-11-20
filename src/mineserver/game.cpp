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

#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <mineserver/localization.h>
#include <mineserver/network/client.h>
#include <mineserver/network/message/chat.h>
#include <mineserver/game.h>

bool is_dead(Mineserver::Network_Client::pointer_t client) {
  return client->alive() == false;
}

void Mineserver::Game::run()
{
  //std::cout << "Tick!" << std::endl;
  //std::cout << "There are " << m_clients.size() << " clients connected!" << std::endl;

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
        m_players.erase(m_clientMap[client]->getName());
        m_clientMap.erase(client);
      }

      continue;
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

void Mineserver::Game::chat(Mineserver::Network_Client::pointer_t client, std::string message)
{
	Mineserver::Game_Player::pointer_t player = m_clientMap[client];

	boost::shared_ptr<Mineserver::Network_Message_Chat> chatMessage = boost::make_shared<Mineserver::Network_Message_Chat>();
	chatMessage->mid = 0x03;
	chatMessage->message = "<" + player->getName() + "> " + message;

	for (clientList_t::iterator it=m_clients.begin();it!=m_clients.end();++it) {
		if (*it == client) {
      //continue;
		}

		client->outgoing().push_back(chatMessage);
	}
}
