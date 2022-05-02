/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** IHeaderParsing
*/

#ifndef IHEADERPARSING_HPP_
#define IHEADERPARSING_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "ziapi/Http.hpp"

using namespace ziapi::http;
using namespace ziapi::http::reason;

class IHeaderParsing
{
    public:
        virtual ~IHeaderParsing() = default;
        virtual Request requestParsing(const std::string &strSrc) = 0;
        virtual std::string ResponseParsing(Response) = 0;
    protected:
    private:
        virtual void ResponseGetCode(std::string &strReturn, const Code &target) = 0;
        virtual void requestGetHeader(std::string &strSrc) = 0;
};

#endif /* !IHEADERPARSING_HPP_ */
