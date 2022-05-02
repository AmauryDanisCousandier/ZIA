/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** HeaderParsing
*/

#ifndef HEADERPARSING_HPP_
#define HEADERPARSING_HPP_

#include "IHeaderParsing.hpp"

class HeaderParsing : public IHeaderParsing
{
    public:
        HeaderParsing();
        ~HeaderParsing();
        virtual Request requestParsing(const std::string &strSrc);
        virtual std::string ResponseParsing(Response);

    protected:
    private:
        virtual void ResponseGetCode(std::string &strReturn, const Code &target);
        virtual void requestGetHeader(std::string &strSrc);
};

#endif /* !HEADERPARSING_HPP_ */
