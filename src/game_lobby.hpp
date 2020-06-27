#pragma once

#include <map>

#include "game_packet.hpp"
#include "game_player.hpp"

class game_lobby {
public:
    game_player::id_t join(game_player::ptr player);

    void leave(game_player::ptr player);

    void broadcast(const game_player::id_t& id, game_packet& packet);

private:
    std::map<game_player::id_t, game_player::ptr> _players;
};

