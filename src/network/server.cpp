/*
** EPITECH PROJECT, 2021
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** server.cpp
*/

#include "../../includes/network/server.hpp"

tcp_server::tcp_server(boost::asio::io_context& io_context) : _ioContext(io_context), _acceptor(io_context, tcp::endpoint(tcp::v4(), 8080))
{
    start_accept();
}

void tcp_server::start_accept()
{
    tcp_connection::pointer new_connection = tcp_connection::create(_ioContext);

    _acceptor.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
        boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error)
{
    if (!error) {
        new_connection->start();
    }
    start_accept();
}