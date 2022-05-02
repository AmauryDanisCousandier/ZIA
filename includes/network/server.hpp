/*
** EPITECH PROJECT, 2021
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** server.hpp
*/

#include "./connection.hpp"
#include "../network.hpp"
#include "ziapi/Module.hpp"

using namespace ziapi;

class tcp_server
{
public:
    tcp_server(boost::asio::io_context& io_context);
    void PushRequest(void);
    void PopRequest(void);
private:
    boost::asio::io_context& _ioContext;
    size_t _threadPoolSize;
    std::vector<boost::shared_ptr<boost::thread>> _threadPool;
    tcp::acceptor _acceptor;

    void start_accept();
    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);
};