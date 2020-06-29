cmake_minimum_required(VERSION 3.1)

find_package(Threads REQUIRED)

set(server_LIBRARIES Threads::Threads)
set(server_DEPENDENCIES asio)

set(server_SOURCES main.cpp game_packet.cpp game_server.cpp game_client.cpp
    game_lobby.cpp game_player.cpp data_types.cpp)

set(server_HEADERS game_packet.hpp game_server.hpp game_client.hpp
    game_lobby.hpp game_player.hpp data_types.hpp)

add_executable(server ${server_SOURCES} ${server_HEADERS})

add_dependencies(server ${server_DEPENDENCIES})

target_link_libraries(server PUBLIC ${server_LIBRARIES})
