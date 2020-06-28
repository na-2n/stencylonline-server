#include "game_packet.hpp"

#include <iostream>

game_packet::game_packet(header_type type)
    : _length{0},
      _id{0},
      _header_length{type},
      _encoded{false}
{
}

game_packet::game_packet(const packet_id_t& id, header_type type)
    : _length{0},
      _id{id},
      _header_length{type},
      _encoded{false}
{
}

bool game_packet::decode_header()
{
    std::memcpy(&_length, _data, sizeof(packet_length_t));

    if (_length > body_length_max) {
        _length = body_length_max;

        return false;
    }

    std::memcpy(&_id, _data + sizeof(packet_length_t), sizeof(packet_id_t));

    if (_header_length == header_server) {
        std::memcpy(&_player_id, _data + sizeof(packet_length_t) + sizeof(packet_id_t), sizeof(player_id_t));
    }

    return _length >= 0;
}

bool game_packet::encode_header()
{
    std::memcpy(_data, &_length, sizeof(packet_length_t));
    std::memcpy(_data + sizeof(packet_length_t), &_id, sizeof(packet_id_t));

    if (_header_length == header_server) {
        std::memcpy(_data + sizeof(packet_length_t) + sizeof(packet_id_t), &_player_id, sizeof(player_id_t));
    }

    return _encoded = true;
}

