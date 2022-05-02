/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** threadFunction
*/

#ifndef THREADFUNCTION_HPP_
#define THREADFUNCTION_HPP_

#include <iostream>
#include "QueueManagement/RequestInputQueue.hpp"
#include "QueueManagement/ResponseOutputQueue.hpp"
#include "queue.hpp"
#include "optional"
#include "ziapi/Http.hpp"
#include "ziapi/Module.hpp"
#include "dylib/dylib.hpp"

std::vector<ziapi::IHandlerModule*> open_share_lib();
std::vector<std::string> listModule(void);
ziapi::IHandlerModule *openTheName(std::string file);


static void threadFunction()
{
    RequestInputQueue reqInp;
    ResponseOutputQueue resOut;
    Response res;

    /* Default Value */
    res.status_code = Code::kNotFound; 
    res.reason = reason::kNotFound;
    
    if (reqInp.Size() > 0) {
        std::optional<std::pair<Request, Context>> recup = reqInp.Pop();
        std::vector<std::string> libs = listModule();

        for (auto file : libs) {
            dylib cdylib("../lib/libPHPModule", dylib::extension);
            auto hello = cdylib.get_function<ziapi::IHandlerModule*(void)>("getInstanceClass");
            if (file.length() < 5 || file.substr(0, 5) != "boost") {
                #if defined(__unix__)
                    dylib cdylib("../lib/lib" + file, dylib::extension);
                #else
                    dylib cdylib(file, dylib::extension);
                #endif
                auto hello = cdylib.get_function<ziapi::IHandlerModule*(void)>("getInstanceClass");
                ziapi::IHandlerModule *lib = hello();
                if (lib->ShouldHandle(recup.value().second, recup.value().first))
                    lib->Handle(recup.value().second, recup.value().first, res);
            }
        }
        res.version = recup.value().first.version;
        resOut.Push(std::make_pair(res, recup.value().second));
    }
}

#endif /* !THREADFUNCTION_HPP_ */