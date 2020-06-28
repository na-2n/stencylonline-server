#include "game_lobby.hpp"

#include <iostream>

player_id_t game_lobby::join(game_player::ptr player)
{
    player_id_t id = 0;

    while (_players.find(id) != _players.end()) {
        id++;
    }

    _players[id] = player;

    game_packet join_pkt{game_packet::id_join};

    if (join_pkt.encode_header()) {
        broadcast(id, join_pkt);
    }

    if (!_players.empty()) {
        game_packet init_pkt{game_packet::id_join, game_packet::header_server};

        //init_pkt.set_body_length(1);

        if (init_pkt.encode_header()) {
            for (auto& kv : _players) {
                if (kv.first != id) {
                    init_pkt.set_player_id(kv.first);

                    //init_pkt.body()[0] = kv.first;

                    player->send_packet(init_pkt);
                }
            }
        }
    }

    std::printf("player %u joined!\n", id);

    return id;
}

void game_lobby::leave(game_player::ptr player)
{
    std::printf("player %u left!\n", player->id());

    game_packet dc_pkt{game_packet::id_leave};

    //dc_pkt.encode_header();

    broadcast(player->id(), dc_pkt);

    _players.erase(player->id());

    //std::printf("remaining players: %lu\n", _players.size());
}

void game_lobby::broadcast(const player_id_t& id, game_packet& packet)
{
    packet.set_player_id(id);

    if (!packet.encode_header()) {
        return;
    }

    for (auto& kv : _players) {
        if (kv.first != id) {
            kv.second->send_packet(packet);
        }
    }
}

