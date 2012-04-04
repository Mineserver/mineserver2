/*
  Copyright (c) 2012, The Mineserver Project
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
#include <vector>
#include <mineserver/game/player.h>
#include <mineserver/game.h>
#include <mineserver/network/client.h>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#ifndef COMMAND_H
#define	COMMAND_H

namespace Mineserver 
{
  class Command : public boost::enable_shared_from_this<Mineserver::Command> {
  public:
    Command(std::string cmd, boost::shared_ptr<Mineserver::Network_Client> m_client, boost::shared_ptr<Mineserver::Game_Player> m_player, bool ig);
    void execute(Mineserver::Game::pointer_t game, Mineserver::Game::clientList_t, Mineserver::Network_Client::pointer_t client);
    virtual ~Command();
  private:
    bool inGame;
    std::string command;
    std::vector<std::string> args;
    int argc;
    boost::shared_ptr<Mineserver::Game_Player> m_player;
    boost::shared_ptr<Mineserver::Network_Client> m_client;
  };
}

#endif
