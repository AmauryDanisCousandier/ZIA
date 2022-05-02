/*
** EPITECH PROJECT, 2021
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** connection.hpp
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include "../network.hpp"
#include "../queue.hpp"
#include "../threadFunction.hpp"

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;
    //creates the connection. Returns a pointer to tcp_connection obejct
    static pointer create(boost::asio::io_context& io_context)
    {
        return pointer(new tcp_connection(io_context));
    }
    //returns a pointer to the socket
    tcp::socket& socket();
    //starts the connection
    void start();
    //closes the socket
    void stop();

private:
    tcp::socket _socket;
    std::string _message; //string for response
    std::array<char, 8192> _reqBuff; //buffer for request

    //constructor for tcp_connection obj
    tcp_connection(boost::asio::io_context& io_context) : _socket(io_context) {}

    void getRequest(void);

    void sendResponse(void);
    //do the write operation
    void handle_write(const boost::system::error_code&, size_t size);
    //do the read operation
    void handle_read(const boost::system::error_code&, size_t size);

};

#endif /*CONNECTION_HPP_*/
