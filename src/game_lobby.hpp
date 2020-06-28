#pragma once

#include <map>

#include "data_types.hpp"
#include "game_packet.hpp"
#include "game_player.hpp"

class game_lobby {
public:
    player_id_t join(game_player::ptr player);

    void leave(game_player::ptr player);

    void broadcast(const player_id_t& id, game_packet& packet);

private:
    std::map<player_id_t, game_player::ptr> _players;
};

