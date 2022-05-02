/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** IRequestInputQueue
*/

#ifndef IREQUESTINPUTQUEUE_HPP_
#define IREQUESTINPUTQUEUE_HPP_

#include "ziapi/Http.hpp"
#include <list>
#include <mutex>
using namespace ziapi::http;

class IRequestInputQueue
{
    public:
        virtual ~IRequestInputQueue() = default;
        [[nodiscard]] virtual std::optional<std::pair<Request, Context>> Pop() = 0;

        [[nodiscard]] virtual std::size_t Size() const noexcept = 0;

        virtual void Wait() noexcept = 0;
    protected:
    private:
};

#endif /* !IREQUESTINPUTQUEUE_HPP_ */
