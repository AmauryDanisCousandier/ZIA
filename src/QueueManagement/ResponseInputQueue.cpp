/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** ResponseInputQueue
*/

#include "../../includes/QueueManagement/ResponseInputQueue.hpp"

ResponseInputQueue::ResponseInputQueue()
{
}

ResponseInputQueue::~ResponseInputQueue()
{
}

[[nodiscard]] std::optional<std::pair<Response, Context>> ResponseInputQueue::Pop()
{
    gResponseMutex.lock();
    if (gResponseQueue.size() >= 1) {
        std::pair<Response, Context> pTmp = gResponseQueue.front();
        gResponseQueue.erase(gResponseQueue.begin());
        gResponseMutex.unlock();
        std::optional oTmp { pTmp };
        return (oTmp);
    }
    gResponseMutex.unlock();
    return (std::nullopt);
}

[[nodiscard]] std::size_t ResponseInputQueue::Size() const noexcept
{
    gResponseMutex.lock();
    std::size_t iTmp = gResponseQueue.size();
    gResponseMutex.unlock();
    return (iTmp);
}

void ResponseInputQueue::Wait() noexcept
{
}