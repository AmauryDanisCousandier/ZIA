/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** ConfigManagement
*/

#ifndef CONFIGMANAGEMENT_HPP_
#define CONFIGMANAGEMENT_HPP_

#include <map>

#include "./IConfigManagement.hpp"
#include "ziapi/Config.hpp"

using Node = ziapi::config::Node;

class ConfigManagement : public IConfigManagement
{
    public:
        ConfigManagement(const std::string &filePath);
        ~ConfigManagement();

        /* GETTER */
        virtual const std::string &getFilePath(void) const;
        virtual const std::string getFileContent(void) const;
        std::string getKey(std::string content);
        std::string getArray(std::string content);
        std::string getDict(std::string content);

        std::vector<std::vector<std::string>> &getServer();
        std::vector<std::vector<std::string>> &getModules();
        Node &getNode();

        virtual int checkFilePath(void);
        bool checkExtension();
        int checkSpace(std::string line);

        /* PARSER */
        void parserServer();
        void parserModules();

        Node buildNodeConfig();  

    private:
        std::string _filePath;
        std::ostringstream _fileContent;
        bool _isGoodFile;

        std::vector<std::vector<std::string>> _server;
        std::vector<std::vector<std::string>> _modules;

        Node _config;
};

#endif /* !CONFIGMANAGEMENT_HPP_ */
