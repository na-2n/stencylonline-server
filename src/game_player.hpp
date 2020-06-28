#pragma once

#include <memory>

#include "game_packet.hpp"
#include "data_types.hpp"

class game_player {
public:
    using ptr = std::shared_ptr<game_player>;

    virtual player_id_t id() const = 0;

    virtual void send_packet(game_packet& packet) = 0;
};

