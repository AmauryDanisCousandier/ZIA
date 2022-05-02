/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** RequestOutputQueue
*/

#ifndef REQUESTOUTPUTQUEUE_HPP_
#define REQUESTOUTPUTQUEUE_HPP_

#include "ziapi/Http.hpp"
#include <list>
#include <mutex>
#include "../queue.hpp"
using namespace ziapi::http;

class RequestOutputQueue : public IRequestOutputQueue
{
    public:
        RequestOutputQueue();
        ~RequestOutputQueue();

        virtual void Push(std::pair<Request, Context> &&req);

        [[nodiscard]] virtual std::size_t Size() const noexcept;
    protected:
    private:
};

#endif /* !RESPONSEOUTPUTQUEUE_HPP_ */
