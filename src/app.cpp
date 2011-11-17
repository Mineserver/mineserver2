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

#include <string>
#include <iostream>
#include <cstdio>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <mineserver/game.h>
#include <mineserver/network/protocol/notch/protocol.h>
#include <mineserver/network/server.h>

#include <mineserver/watcher/keepalive.h>
#include <mineserver/watcher/login.h>
#include <mineserver/watcher/handshake.h>
#include <mineserver/watcher/serverlistping.h>

int main()
{
  boost::asio::io_service service;

  Mineserver::Game::pointer_t game = boost::make_shared<Mineserver::Game>();
  Mineserver::Network_Protocol::pointer_t protocol = boost::make_shared<Mineserver::Network_Protocol_Notch_Protocol>();
  Mineserver::Network_Server::pointer_t server = boost::make_shared<Mineserver::Network_Server>(game, protocol, &service);

  game->addMessageWatcher(0x00, Mineserver::Watcher_KeepAlive());
  game->addMessageWatcher(0x01, Mineserver::Watcher_Login());
  game->addMessageWatcher(0x02, Mineserver::Watcher_Handshake());
  game->addMessageWatcher(0xFE, Mineserver::Watcher_ServerListPing());

  while (true) {
    try {
      service.poll();
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }

    try {
      game->run();
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }

    boost::this_thread::sleep(boost::posix_time::milliseconds(50));
  }

  return 0;
}
