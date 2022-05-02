/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** IResponseOutputQueue
*/

#ifndef IRESPONSEOUTPUTQUEUE_HPP_
#define IRESPONSEOUTPUTQUEUE_HPP_

#include "ziapi/Http.hpp"
#include <list>
#include <mutex>
using namespace ziapi::http;

class IResponseOutputQueue
{
    public:
        virtual ~IResponseOutputQueue() = default;

    protected:
    private:
};

#endif /* !IRESPONSEOUTPUTQUEUE_HPP_ */
