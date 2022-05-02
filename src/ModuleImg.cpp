/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** Handler
*/

#include "../includes/ModuleImg.hpp"
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
    return new ModuleImg();
}

void ModuleImg::Init(const ziapi::config::Node &cfg)  
{
    root_ = "/module.php"; 
}

[[nodiscard]] ziapi::Version ModuleImg::GetVersion() const noexcept  
{
    return {4, 0, 0};
}

[[nodiscard]] ziapi::Version ModuleImg::GetCompatibleApiVersion() const noexcept  
{
    return {4, 0, 0};
}

[[nodiscard]] const char *ModuleImg::GetName() const noexcept  
{
    return "myModule";
}


[[nodiscard]] const char *ModuleImg::GetDescription() const noexcept  
{
    return "Give access to a filesystem over HTTP";
}

[[nodiscard]] double ModuleImg::GetHandlerPriority() const noexcept  
{
    return 0.5f;
}

[[nodiscard]] bool ModuleImg::ShouldHandle(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const  
{
    //     We only want to handle GET requests.
    return (std::string::npos != req.target.find(".jpeg") ||\
    std::string::npos != req.target.find(".png") ||\
    std::string::npos != req.target.find(".gif"));
}

void ModuleImg::Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)  
{
    auto filepath = std::filesystem::path(std::string(".") + req.target);
    std::error_code ec;

    if (!std::filesystem::exists(std::string(".") + req.target)) return;

    std::ifstream file_stream(filepath.filename());
    std::ostringstream ss;
    ss << file_stream.rdbuf();
    res.body = ss.str();
    
    if (std::string::npos != req.target.find(".jpeg")) {
        res.headers["Content-Type"] = "image/jpeg";
    }
    if (std::string::npos != req.target.find(".png")) {
        res.headers["Content-Type"] = "image/png";
    }
    if (std::string::npos != req.target.find(".gif")) {
        res.headers["Content-Type"] = "image/gif";
    }
    res.headers["Content-Length"] = std::to_string(res.body.length());
    res.status_code = ziapi::http::Code::kOK;
    res.reason = ziapi::http::reason::kOK;
    res.version = ziapi::http::Version::kV1_1;
}
