/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-yearendproject-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** main.cpp
*/

#include "../includes/zia.hpp"
#include "../includes/network.hpp"
#include "../includes/network/server.hpp"
#include "../includes/QueueManagement/ResponseInputQueue.hpp"
#include "../includes/QueueManagement/RequestOutputQueue.hpp"
#include "dylib/dylib.hpp"
#include "../includes/network.hpp"
// #include "../includes/network/coreNetwork.hpp"

void help(void)
{
    std::cerr << "Usage:\n\t./zia [port] [files]" << std::endl;
    std::cerr << "[port] port which will be used by the server to communicate ex 8080" << std::endl;
    std::cerr << "[files] root for files used for filesystem ex ./webserver/" << std::endl;
    exit(0);
}

void badUsage(void)
{
    std::cerr << "\t\tbad usage." << std::endl;
    std::cerr << "try turning around yourself and scream I LOVE POTATOES" << std::endl;
    std::cerr << "there's a lil more chance that you get me to work this way" << std::endl;
    std::cerr << "the cake is a lie, potatoes aren't" << std::endl;
    std::cerr << "serioulsy will you ask for --help ?" << std::endl;
    exit(84);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Error Usage" << std::endl;
        help();
        return (84);
    }
    ConfigManagement config(argv[1]);
    boost::asio::io_context io_context;
    tcp_server server(io_context);
    io_context.run();
    return (0);
}