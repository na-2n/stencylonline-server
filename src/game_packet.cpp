#include "game_packet.hpp"

game_packet::game_packet()
    : _length{0}
{
}

game_packet::game_packet(const game_packet::id_t& id)
    : _id{id},
      _length{0}
{
}

bool game_packet::init_with(const game_packet::id_t& id, char* data, const game_packet::len_t& len)
{
    if (len > body_length_max) {
        return false;
    }

    _id = id;
    _length = len;

    if (!encode_header()) {
        return false;
    }

    std::memcpy(body(), data, len);

    return true;
}

bool game_packet::decode_header()
{
    std::memcpy(&_length, _data, sizeof(len_t));

    if (_length > body_length_max) {
        _length = 0;

        return false;
    }

    _id = static_cast<id_t>(_data[sizeof(len_t)]);

    if (_id >= _id_max) {
        _id = 0;

        return false;
    }

    return _length >= 0;
}

bool game_packet::encode_header()
{
    std::memcpy(_data, &_length, sizeof(len_t));

    _data[sizeof(len_t)] = _id;

    return true;
}

