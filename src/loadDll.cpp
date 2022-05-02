#include "dylib/dylib.hpp"
#include "ziapi/Module.hpp"
#include <iostream>

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
    #include <windows.h>
#else
    #define EXPORT
    #include <dlfcn.h>
#endif

extern "C" EXPORT ziapi::IHandlerModule *getInstanceClass(void);

#if defined(__unix__)
#include <dirent.h>
#define PATH_TO_LIB std::string("../lib/")

std::vector<std::string> read_dir(void)
{
    DIR *dir; struct dirent *diread;
    std::vector<std::string> files;

    if ((dir = opendir(PATH_TO_LIB.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            std::string str(diread->d_name);
            if (str.substr(str.find(".")) == std::string(".so")) {
                str = str.substr(3);
                str.resize(str.size() - 3);
                files.push_back(str);
            }
        }
        closedir (dir);
    }

    return files;
}
#elif defined(_WIN32)

#include <filesystem>


#define PATH_TO_LIB std::string(".\\")

std::vector<std::string> read_dir(void)
{
    std::vector<std::string> files;

    for (const auto & file : std::filesystem::directory_iterator(PATH_TO_LIB)) {
        std::string str(file.path().string());
        
        if (str.substr(str.substr(str.find(".") + 1).find(".") + 1) == std::string(".dll")) {
            str = str.substr(2);
            str.resize(str.size() - 4);
            files.push_back(str);
        }
    }

    return (files);
}

#endif


std::vector<std::string> listModule(void)
{
    return (read_dir());
}

ziapi::IHandlerModule *openTheName(std::string file)
{
    if (file.length() < 5 || file.substr(0, 5) != "boost") {
        #if defined(__unix__)
            dylib test("../lib/lib" + file, dylib::extension);
        #else
            dylib test(file, dylib::extension);
        #endif
        auto hello = test.get_function<ziapi::IHandlerModule*(void)>("getInstanceClass");
        return hello();
    }
    return nullptr;
}

std::vector<ziapi::IHandlerModule*> open_share_lib(void)
{
    std::vector<std::string> files = read_dir();
    std::vector<ziapi::IHandlerModule*> myLibs;
    // CREATE create;
    // DESTROY destroy;
    // void *handle;

    for (auto file : files) {
        if (file.length() < 5 || file.substr(0, 5) != "boost") {
            #if defined(__unix__)
                dylib test("../lib/lib" + file, dylib::extension);
            #else
                dylib test(file, dylib::extension);
            #endif
            auto hello = test.get_function<ziapi::IHandlerModule*(void)>("getInstanceClass");
            myLibs.push_back(hello());
        }
    }
    return myLibs;
}