/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** IConfigManagement
*/

#ifndef ICONFIGMANAGEMENT_HPP_
#define ICONFIGMANAGEMENT_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class IConfigManagement
{
    public:
        virtual ~IConfigManagement() = default;
        virtual const std::string &getFilePath(void) const = 0;
        virtual int checkFilePath(void) = 0;

    protected:
    private:
};

#endif /* !ICONFIGMANAGEMENT_HPP_ */