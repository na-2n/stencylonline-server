#pragma once

#include <memory>
#include <deque>
#include <chrono>

#include <asio.hpp>

#include "data_types.hpp"
#include "game_packet.hpp"
#include "game_player.hpp"
#include "game_lobby.hpp"

using asio::ip::tcp;
using time_point = std::chrono::steady_clock::time_point;

class game_client
    : public std::enable_shared_from_this<game_client>,
      public game_player
{
public:
    game_client(tcp::socket sock, game_lobby& lobby);

    void start();

    void send(game_packet& pkt);

    inline game_player::id_t id() const override
    {
        return _id;
    }

    void send_packet(game_packet& packet) override;

private:
    void do_read_header();

    void do_read_body();

    void do_write();

    void handle_packet(game_packet& packet);

    std::chrono::milliseconds _dc_treshold{5000};
    std::chrono::steady_clock _clock;
    time_point _last_ping;

    game_player::id_t _id;

    std::deque<game_packet> _msg_queue;
    tcp::socket _sock;
    game_packet _packet;
    game_lobby& _lobby;
};

