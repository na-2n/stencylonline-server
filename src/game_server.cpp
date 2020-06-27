#include "game_server.hpp"

#include <iostream>
#include <memory>

#include "game_client.hpp"

game_server::game_server(asio::io_context& io_ctx, const tcp::endpoint& endpoint)
    : _acceptor{io_ctx, endpoint}
{
    _acceptor.listen();

    std::cout << "listening on :" << endpoint.port() << std::endl;

    do_accept();
}

void game_server::do_accept()
{
    _acceptor.async_accept(
            [this](std::error_code ec, tcp::socket sock)
            {
                if (!ec) {
                    std::cout << "incoming connection" << std::endl;

                    std::make_shared<game_client>(std::move(sock), _lobby)->start();
                }

                do_accept();
            });
}

