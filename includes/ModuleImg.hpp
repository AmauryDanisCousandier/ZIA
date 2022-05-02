/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles
** File description:
** ModuleImg
*/

#ifndef MODULEIMG_HPP_
#define MODULEIMG_HPP_

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "ziapi/Config.hpp"
#include "ziapi/Module.hpp"


class ModuleImg : public ziapi::IHandlerModule {
public:
    void Init(const ziapi::config::Node &cfg) override;

    [[nodiscard]] ziapi::Version GetVersion() const noexcept override;

    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override;

    [[nodiscard]] const char *GetName() const noexcept override;


    [[nodiscard]] const char *GetDescription() const noexcept override;

    [[nodiscard]] double GetHandlerPriority() const noexcept override;

    [[nodiscard]] bool ShouldHandle(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const override;

    void Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res) override;

private:
    std::string root_;
};

#endif /* !MODULEIMG_HPP_ */
