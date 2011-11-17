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

#include <mineserver/network/client.h>
#include <mineserver/game.h>

bool is_dead(Mineserver::Network_Client::pointer_t client) {
  return client->alive() == false;
}

void Mineserver::Game::run()
{
  //std::cout << "Tick!" << std::endl;
  //std::cout << "There are " << m_clients.size() << " clients connected!" << std::endl;

  for (std::vector<Mineserver::Network_Client::pointer_t>::iterator client_it=m_clients.begin();client_it!=m_clients.end();++client_it) {
    Mineserver::Network_Client::pointer_t client(*client_it);

    if (!client || client->alive() == false) {
      std::cout << "Found a dead client..?" << std::endl;
      continue;
    }

    // 1200 in-game ticks = timed out, inactive ticks = ticks past since last keep-alive:
    if (client->inactiveTicks() > 1200) {
      std::cout << "Client timed-out." << std::endl;
      client->timedOut();
      if (!client || client->alive() == false) {
        continue;
      }
    }

    std::cout << "There are " << client->incoming().size() << " messages." << std::endl;

    for (std::vector<Mineserver::Network_Message::pointer_t>::iterator message_it=client->incoming().begin();message_it!=client->incoming().end();++message_it) {
      Mineserver::Network_Message::pointer_t message = *message_it;
      m_messageWatchers[message->mid](shared_from_this(), client, message);
    }

    std::cout << "Watchers done." << std::endl;

    client->incoming().clear();

    // +1 in-game tick, and anything else:
    // possibly send keep-alive?
    client->run();

    client->write();
  }

  m_clients.erase(remove_if(m_clients.begin(), m_clients.end(), is_dead), m_clients.end());
}
