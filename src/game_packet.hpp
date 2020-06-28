#pragma once

#include <cstdlib>
#include <cstring>

#include "data_types.hpp"

class game_packet {
public:
    enum { body_length_max = 0xFF };

    enum header_type {
        header_client = sizeof(packet_id_t) + sizeof(packet_length_t),
        header_server = header_client + sizeof(player_id_t)
    };

    enum identifier {
        id_ping     = 0x00,

        id_join     = 0x01,
        id_leave    = 0x02,

        id_spawn    = 0x03,
        id_position = 0x04,

        _id_max
    };

    game_packet(header_type type = header_client);

    game_packet(const packet_id_t& id, header_type type = header_client);

    inline const char* data() const
    {
        return _data;
    }

    inline char* data()
    {
        return _data;
    }

    inline std::size_t length() const
    {
        return _header_length + _length;
    }

    inline const char* body() const
    {
        return _data + _header_length;
    }

    inline char* body()
    {
        return _data + _header_length;
    }

    inline std::size_t body_length() const
    {
        return _length;
    }

    inline void set_body_length(const packet_length_t& len)
    {
        _length = len;

        if (_encoded) {
            std::memcpy(_data, &_length, sizeof(packet_length_t));
        }
    }

    inline player_id_t player_id()
    {
        return _player_id;
    }

    inline void set_player_id(const player_id_t& player_id)
    {
        _header_length = header_server;

        _player_id = player_id;

        if (_encoded) {
            std::memcpy(_data + header_client, &_player_id, sizeof(player_id_t));
        }
    }

    inline identifier id() const
    {
        return static_cast<identifier>(_id);
    }

    virtual bool decode_header();

    virtual bool encode_header();

private:
    bool _encoded;

    header_type _header_length;
    packet_length_t _length;
    packet_id_t _id;
    player_id_t _player_id;
    char _data[header_server + body_length_max];
};

