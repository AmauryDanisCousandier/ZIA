/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** Handler
*/

#include "../includes/Handler.hpp"
#include <iostream>
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
    return new MyModule();
}

void MyModule::Init(const ziapi::config::Node &cfg)  
{
    root_ = "/module.php"; 
}

[[nodiscard]] ziapi::Version MyModule::GetVersion() const noexcept  
{
    return {4, 0, 0};
}

[[nodiscard]] ziapi::Version MyModule::GetCompatibleApiVersion() const noexcept  
{
    return {4, 0, 0};
}

[[nodiscard]] const char *MyModule::GetName() const noexcept  
{
    return "myModule";
}


[[nodiscard]] const char *MyModule::GetDescription() const noexcept  
{
    return "Give access to a filesystem over HTTP";
}

[[nodiscard]] double MyModule::GetHandlerPriority() const noexcept  
{
    /// Our module doesn't have any specific priority requirements.
    /*std::string cmd = std::string("php -f ") + std::string(root_);
    std::array<char, 128> buffer;
    std::string result;
    #if defined(_WIN32)
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
    #else
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    #endif 
    if (!pipe) {
        // res.status_code = ziapi::http::Code::kNotFound;
        // res.reason = ziapi::http::reason::kNotFound;
        return;
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    // res.body = result;
    // res.status_code = ziapi::http::Code::kOK;
    // res.reason = ziapi::http::reason::kOK;*/
    return 0.5f;
}

[[nodiscard]] bool MyModule::ShouldHandle(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const  
{
    ///     We only want to handle GET requests.
    return (std::string::npos != req.target.find(".php") || std::string::npos != req.target.find(".htm"));
}

void MyModule::Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)  
{
    std::string cmd = std::string("php .") + req.target;
    std::array<char, 128> buffer;
    std::string result;
    if (!std::filesystem::exists(std::string(".") + req.target)) return;

    #if defined(_WIN32)
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
    #else
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    #endif 
    if (!pipe) {
        res.status_code = ziapi::http::Code::kInternalServerError;
        res.reason = ziapi::http::reason::kInternalServerError;
        return;
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    std::cout << result << std::endl;
    res.body = result;
    res.headers["Content-Type"] = "text/html";
    res.headers["Content-Length"] = std::to_string(result.length());
    res.status_code = ziapi::http::Code::kOK;
    res.reason = ziapi::http::reason::kOK;
    res.version = ziapi::http::Version::kV1_1;
}
