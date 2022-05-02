/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** ResponseInputQueue
*/

#ifndef RESPONSEINPUTQUEUE_HPP_
#define RESPONSEINPUTQUEUE_HPP_

#include "ziapi/Http.hpp"
#include <iostream>
#include <list>
#include <mutex>
#include <optional>
#include "../queue.hpp"
using namespace ziapi::http;

class ResponseInputQueue : public IResponseInputQueue
{
    public:
        ResponseInputQueue();
        ~ResponseInputQueue();

        [[nodiscard]] virtual std::optional<std::pair<Response, Context>> Pop();

        [[nodiscard]] virtual std::size_t Size() const noexcept;

        virtual void Wait() noexcept;

    protected:
    private:
};

#endif /* !RESPONSEINPUTQUEUE_HPP_ */
