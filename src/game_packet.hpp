#pragma once

#include <cstdlib>
#include <cstring>

#include "data_types.hpp"

class game_packet {
public:
    using id_t = unsigned char;
    using len_t = unsigned char;

    enum { header_length = sizeof(id_t) + sizeof(len_t) };
    enum { body_length_max = 0xFF };

    enum identifier {
        /*
        id_connect  = 0x01,
        id_ping     = 0x02,
        id_pong     = 0x03,

        id_join     = 0x05,
        id_leave    = 0x06,

        id_data     = 0x10,
        id_position = 0x11,
        id_action   = 0x12,
        */

        id_ping     = 0x00,

        id_join     = 0x01,
        id_leave    = 0x02,

        id_spawn    = 0x03,
        id_position = 0x04,

        _id_max
    };

    game_packet();

    game_packet(const id_t& id);

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
        return header_length + _length;
    }

    inline const char* body() const
    {
        return _data + header_length;
    }

    inline char* body()
    {
        return _data + header_length;
    }

    inline std::size_t body_length() const
    {
        return _length;
    }

    inline void set_body_length(const std::size_t& len)
    {
        _length = len;
    }

    inline identifier id() const
    {
        return static_cast<identifier>(_id);
    }

    bool init_with(const id_t& id, char* data, const len_t& len);

    template<typename T, std::size_t Size = sizeof(T)>
    inline void append(T* x)
    {
        std::memcpy(body() + _length, x, Size);

        _length += Size;
    }

    virtual bool decode_header();

    virtual bool encode_header();

private:
    len_t _length;
    id_t _id;
    char _data[header_length + body_length_max];
};

