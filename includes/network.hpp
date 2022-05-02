/*
** EPITECH PROJECT, 2021
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** header.hpp
*/

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "QueueManagement/RequestOutputQueue.hpp"
#include "QueueManagement/ResponseInputQueue.hpp"
#include "network/HeaderParsing/HeaderParsing.hpp"

using boost::asio::ip::tcp;