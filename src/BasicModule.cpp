/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** Handler
*/

#include "../includes/BasicModule.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
    #include <windows.h>
#else
    #define EXPORT
    #include <dlfcn.h>
#endif

extern "C" EXPORT ziapi::IHandlerModule *getInstanceClass(void)
{
    return new BasicModule();
}

void BasicModule::Init(const ziapi::config::Node &cfg)  
{
    root_ = "/module.php"; 
}

[[nodiscard]] ziapi::Version BasicModule::GetVersion() const noexcept  
{
    return {4, 0, 0};
}

[[nodiscard]] ziapi::Version BasicModule::GetCompatibleApiVersion() const noexcept  
{
    return {4, 0, 0};
}

[[nodiscard]] const char *BasicModule::GetName() const noexcept  
{
    return "myModule";
}


[[nodiscard]] const char *BasicModule::GetDescription() const noexcept  
{
    return "Give access to a filesystem over HTTP";
}

[[nodiscard]] double BasicModule::GetHandlerPriority() const noexcept  
{
    return 0.5f;
}

[[nodiscard]] bool BasicModule::ShouldHandle(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const  
{
    // We only want to handle GET requests.
    return true;
}

void BasicModule::Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)  
{

    res.body = "<!DOCTYPE html><html><head><title>not found</title></head><body><h1>404 not found</h1></body></html>";
    
    res.headers["Content-Type"] = "text/html";
    res.headers["Content-Length"] = std::to_string(res.body.length());
    res.status_code = ziapi::http::Code::kNotFound;
    res.reason = ziapi::http::reason::kNotFound;
    res.version = ziapi::http::Version::kV1_1;
}
