/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** RequestInputQueue
*/

#ifndef REQUESTINPUTQUEUE_HPP_
#define REQUESTINPUTQUEUE_HPP_

#include "IRequestInputQueue.hpp"
#include "../queue.hpp"

class RequestInputQueue : public IRequestInputQueue
{
    public:
        RequestInputQueue();
        ~RequestInputQueue();
        
        [[nodiscard]] virtual std::optional<std::pair<Request, Context>> Pop();

        [[nodiscard]] virtual std::size_t Size() const noexcept;

        virtual void Wait() noexcept;

    protected:
    private:
};

#endif /* !REQUESTINPUTQUEUE_HPP_ */
