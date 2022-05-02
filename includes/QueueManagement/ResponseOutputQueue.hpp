/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** ResponseOutputQueue
*/

#ifndef RESPONSEOUTPUTQUEUE_HPP_
#define RESPONSEOUTPUTQUEUE_HPP_

#include "IResponseOutputQueue.hpp"
#include "../queue.hpp"

class ResponseOutputQueue : public IResponseOutputQueue
{
    public:
        ResponseOutputQueue();
        ~ResponseOutputQueue();
        
        virtual void Push(std::pair<Response, Context> &&req);

        [[nodiscard]] virtual std::size_t Size() const noexcept;
    protected:
    private:
};

#endif /* !RESPONSEOUTPUTQUEUE_HPP_ */
