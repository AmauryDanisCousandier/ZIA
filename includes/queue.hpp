/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** Queue
*/

#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include <list>
#include <mutex>
#include "ziapi/Http.hpp"
using namespace ziapi::http;

extern std::list<std::pair<Request, Context>> gRequestQueue;
extern std::mutex gRequestMutex;
extern std::list<std::pair<Response, Context>> gResponseQueue;
extern std::mutex gResponseMutex;

#endif /* !QUEUE_HPP_ */
