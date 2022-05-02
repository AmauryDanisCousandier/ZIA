/*
** EPITECH PROJECT, 2021
** B-YEP-500-MAR-5-1-zia-clovis.gilles
** File description:
** coreNetwork.cpp
*/
#include "../../includes/network/coreNetwork.hpp"
#include "../../includes/network.hpp"

void coreNetwork::Run(http::IRequestOutputQueue &requests, http::IResponseInputQueue &responses)
{
    try {
        boost::asio::io_context io_context;
        tcp_server server(io_context);
        io_context.run();
    }
    catch (std::exception err) {
        std::cerr << "Exeception in coreNetwork->Run => " << err.what() << std::endl;
    }
    
}