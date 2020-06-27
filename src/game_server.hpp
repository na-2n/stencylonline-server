#pragma once

#include <asio.hpp>

#include "game_lobby.hpp"

using asio::ip::tcp;

class game_server {
public:
    game_server(asio::io_context& io_ctx, const tcp::endpoint& endpoint);

private:
    void do_accept();

    tcp::acceptor _acceptor;
    game_lobby _lobby;
};

