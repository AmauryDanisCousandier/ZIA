/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** ResponseOutputQueue
*/

#include "../../includes/QueueManagement/ResponseOutputQueue.hpp"

ResponseOutputQueue::ResponseOutputQueue()
{
}

ResponseOutputQueue::~ResponseOutputQueue()
{
}

void ResponseOutputQueue::Push(std::pair<Response, Context> &&req)
{
    gResponseMutex.lock();
    gResponseQueue.push_back(req);
    gResponseMutex.unlock();
}

[[nodiscard]] std::size_t ResponseOutputQueue::Size() const noexcept
{
    gResponseMutex.lock();
    std::size_t iTmp = gResponseQueue.size();
    gResponseMutex.unlock();
    return (iTmp);
}