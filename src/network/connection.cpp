/*
** EPITECH PROJECT, 2021
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** connection.cpp
*/

#include "../../includes/network/connection.hpp"

std::list<std::pair<Request, Context>> gRequestQueue;
std::mutex gRequestMutex;
std::list<std::pair<Response, Context>> gResponseQueue;
std::mutex gResponseMutex;

void tcp_connection::start()
{
    this->getRequest();
}

void tcp_connection::stop()
{
    this->_socket.close();
}

void tcp_connection::handle_read(const boost::system::error_code&, size_t size)
{
    HeaderParsing parser;
    RequestOutputQueue reqOut;
    ResponseInputQueue resInp;
    Context cTmp;
    cTmp["socket"] = 1;// Temporary
    reqOut.Push(std::make_pair(parser.requestParsing(_reqBuff.data()),cTmp));
    std::thread process(threadFunction); /* Useless, change for a better way*/
    process.join();
    if (resInp.Size() > 0) {
        std::optional<std::pair<Response, Context>> response = resInp.Pop();
        _message = parser.ResponseParsing(response.value().first);
    } else {
        _message = "ERROR";
    }
    this->sendResponse();
    return;
}

void tcp_connection::handle_write(const boost::system::error_code&, size_t size)
{
}

void tcp_connection::getRequest(void)
{
    this->_socket.async_read_some(boost::asio::buffer(this->_reqBuff),
    boost::bind(&tcp_connection::handle_read, shared_from_this(), boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));   
}

void tcp_connection::sendResponse(void)
{
    boost::asio::async_write(_socket, boost::asio::buffer(_message),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

tcp::socket& tcp_connection::socket()
{
    return _socket;
}