#include "game_client.hpp"

game_client::game_client(tcp::socket sock, game_lobby& lobby)
    : _sock{std::move(sock)},
      _lobby{lobby}
{
}

void game_client::send_packet(game_packet& packet)
{
    auto sending = !_msg_queue.empty();

    _msg_queue.push_back(packet);

    if (!sending) {
        do_write();
    }
}

void game_client::start()
{
    _id = _lobby.join(shared_from_this());

    do_read_header();
}

void game_client::do_read_header()
{
    auto self{shared_from_this()};

    asio::async_read(_sock,
        asio::buffer(_packet.data(), game_packet::header_client),
        [this, self](std::error_code ec, std::size_t)
        {
            if (ec == asio::error::connection_reset ||
                    ec == asio::error::eof ||
                    (_last_ping != time_point{} && _clock.now() - _last_ping > _dc_treshold)) {
                _lobby.leave(shared_from_this());

                return;
            }

            if (!ec && _packet.decode_header()) {
                do_read_body();
            }
        });
}

void game_client::do_read_body()
{
    auto self{shared_from_this()};

    asio::async_read(_sock,
        asio::buffer(_packet.body(), _packet.body_length()),
        [this, self](std::error_code ec, std::size_t)
        {
            if (!ec) {
                handle_packet(_packet);

                do_read_header();
            }
        });
}

void game_client::do_write()
{
    auto self{shared_from_this()};

    auto& msg = _msg_queue.front();

    asio::async_write(_sock,
        asio::buffer(msg.data(), msg.length()),
        [this, self](std::error_code ec, std::size_t)
        {
            if (!ec) {
                _msg_queue.pop_front();

                if (!_msg_queue.empty()) {
                    do_write();
                }
            } else {
                _lobby.leave(shared_from_this());
            }
        });
}

void game_client::handle_packet(game_packet& packet)
{
    switch (packet.id()) {
        case game_packet::id_ping:
            _last_ping = _clock.now();

            break;

        default:
            _lobby.broadcast(id(), packet);

            break;
    }
}

