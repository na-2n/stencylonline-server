#include <stdexcept>
#include <iostream>
#include <string>

#include <cstdlib>

#include <asio.hpp>

#include "game_server.hpp"

using asio::ip::tcp;

int main(int argc, char* argv[])
{
    try 
    {
        asio::io_context io_ctx{};

        tcp::endpoint endpoint{tcp::v4(), 8876};

        game_server serv{io_ctx, endpoint};

        io_ctx.run();
    }
    catch (std::exception& err)
    {
        std::cout << err.what() << std::endl;

        return 1;
    }

    return 0;
}

