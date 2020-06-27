#pragma once

#include <memory>

#include "game_packet.hpp"
#include "data_types.hpp"

class game_player {
public:
    using id_t = unsigned char;
    using ptr = std::shared_ptr<game_player>;

    virtual id_t id() const = 0;

    virtual void send_packet(game_packet& packet) = 0;
};

