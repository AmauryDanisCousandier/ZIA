/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** ResquestInputQueue
*/

#include "../../includes/QueueManagement/RequestInputQueue.hpp"

RequestInputQueue::RequestInputQueue()
{
}

RequestInputQueue::~RequestInputQueue()
{
}


[[nodiscard]] std::optional<std::pair<Request, Context>> RequestInputQueue::Pop()
{
    gRequestMutex.lock();
    if (gRequestQueue.size() >= 1) {
        std::pair<Request, Context> pTmp = gRequestQueue.front();
        gRequestQueue.erase(gRequestQueue.begin());
        gRequestMutex.unlock();
        std::optional oTmp { pTmp };
        return (oTmp);
    }
    gRequestMutex.unlock();
    return (std::nullopt);
}

[[nodiscard]] std::size_t RequestInputQueue::Size() const noexcept
{
    gRequestMutex.lock();
    std::size_t iTmp = gRequestQueue.size();
    gRequestMutex.unlock();
    return (iTmp);
}

void RequestInputQueue::Wait() noexcept
{
}