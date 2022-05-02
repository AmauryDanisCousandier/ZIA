/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** HeaderParsing
*/

#include "../../../includes/network/HeaderParsing/HeaderParsing.hpp"

HeaderParsing::HeaderParsing()
{
}

HeaderParsing::~HeaderParsing()
{
}

Request HeaderParsing::requestParsing(const std::string &strSrc)
{
    Request returnValue;
    std::string tmp(strSrc);
    try {
        returnValue.method = tmp.substr(0, tmp.find(" "));
        tmp = tmp.substr(strSrc.find(" ") + 1);
        returnValue.target = tmp.substr(0, tmp.find(" "));
        tmp = tmp.substr(strSrc.find("\r") + 2);
        returnValue.version = Version::kV1_1;
        std::istringstream streamTmp(strSrc.substr(strSrc.find("\r") + 2));
        std::string sTmp;
        while (std::getline(streamTmp, sTmp)) {
            tmp = sTmp.substr(0, sTmp.find(":"));
            returnValue.headers[tmp] = sTmp.substr(tmp.length() + 2, sTmp.find("\r"));
        }
    } catch (std::exception err) {
        std::cerr << "Exception caught in requestPasing: " << err.what() << std::endl;
    }
    return (returnValue);
}

Code& operator ++ (Code& e)
{
    if (e == Code::kHttpVersionNotSupported) {
        throw std::out_of_range("for Code& operator ++ (Code&)");
    }
    e = Code(static_cast<std::underlying_type<Code>::type>(e) + 1);
    return e;
}

std::string HeaderParsing::ResponseParsing(Response response)
{
    std::string strReturn;
    try {
        switch (response.version)
        {
        case Version::kV1:
            strReturn.append("HTTP/10 ");
            break;
        case Version::kV1_1:
            strReturn.append("HTTP/1.1 ");
            break;
        case Version::kV2:
            strReturn.append("HTTP/20 ");
            break;
        case Version::kV3:
            strReturn.append("HTTP/30 ");
            break;
        default:
            break;
        }
        if (strReturn.empty())
            return (strReturn);
        ResponseGetCode(strReturn, response.status_code);
        if (strReturn.empty())
            return (strReturn);
        strReturn.append(response.reason + "\n");
        for (auto i = response.headers.begin(); i != response.headers.end();  i++) {
            strReturn.append(i->first + ": " + i->second + "\n");
        }
        strReturn.append("\n");
        strReturn.append(response.body);
    } catch (std::exception err) {
        std::cerr << "Exception caught in requestPasing: " << err.what() << std::endl;
    }
    return (strReturn);
}

void HeaderParsing::ResponseGetCode(std::string &strReturn, const Code &target)
{
    for(Code e = Code::kContinue; e != Code::kHttpVersionNotSupported; ++e) {
        Code eCurrent = (Code) e;
        if (eCurrent == target)
            strReturn.append(std::to_string((int)e) + " "); 
    }
}

void HeaderParsing::requestGetHeader(std::string &strSrc)
{

}