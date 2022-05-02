/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** RequestOutputQueue
*/

#include "../../includes/QueueManagement/RequestOutputQueue.hpp"

RequestOutputQueue::RequestOutputQueue()
{
}

RequestOutputQueue::~RequestOutputQueue()
{
}

void RequestOutputQueue::Push(std::pair<Request, Context> &&req)
{
    gRequestMutex.lock();
    gRequestQueue.push_back(req);
    gRequestMutex.unlock();
}

[[nodiscard]] std::size_t RequestOutputQueue::Size() const noexcept
{
    gRequestMutex.lock();
    std::size_t iTmp = gRequestQueue.size();
    gRequestMutex.unlock();
    return (iTmp);
}
