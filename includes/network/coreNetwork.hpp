/*
** EPITECH PROJECT, 2021
** B-YEP-500-MAR-5-1-zia-clovis.gilles
** File description:
** coreNetwork.hpp
*/

#ifndef CORENETWORK_HPP_
#define CORENETWORK_HPP_

#include "./server.hpp"
#include "ziapi/Module.hpp"

using namespace ziapi;

class coreNetwork : public ziapi::INetworkModule
{
private:
    /* data */
public:
    void Run(http::IRequestOutputQueue &requests, http::IResponseInputQueue &responses) override;
    //virtual void Terminate(void) override;
};

#endif /*CORENETWORK_HPP_*/