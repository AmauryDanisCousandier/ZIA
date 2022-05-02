/*
** EPITECH PROJECT, 2022
** B-YEP-500-MAR-5-1-zia-clovis.gilles [WSL: Ubuntu-20.04]
** File description:
** ConfigManagement
*/

#include "../../includes/configManager/ConfigManagement.hpp"

ConfigManagement::ConfigManagement(const std::string &filePath) : _filePath(filePath), _isGoodFile(false)
{
    std::ifstream file(_filePath);
    if (file.is_open()) {
        _fileContent << file.rdbuf();
        file.close();
        _isGoodFile = true;
    } else {
        std::cerr << "ERROR: unable to open " << _filePath << std::endl;
        exit(84);
    }
    if (checkFilePath() == 0 && checkExtension()) {
        parserServer();
        parserModules();
        _config = buildNodeConfig();
    } else {
        std::cerr << "ERROR: file " << _filePath << std::endl;
        exit(84);
    }
}

ConfigManagement::~ConfigManagement()
{

}

/* Getter */
const std::string &ConfigManagement::getFilePath(void) const {
    return (_filePath);
}

const std::string ConfigManagement::getFileContent(void) const {
    return (_fileContent.str());
}

std::vector<std::vector<std::string>> &ConfigManagement::getServer() {
    return (_server);
}

std::vector<std::vector<std::string>> &ConfigManagement::getModules() {
    return (_modules);
}

Node &ConfigManagement::getNode() {
    return (_config);
}

int ConfigManagement::checkFilePath(void) {
    if (_isGoodFile == true) return (0);
    return (84);
}

bool ConfigManagement::checkExtension(void) {
    int pos = _filePath.find_last_of("/");
    std::string extension = _filePath.substr(pos + 1);
    pos = extension.find(".");
    extension = extension.substr(pos + 1);

    if (extension == "json") {
        return (true);
    } else
        return (false);
}

int ConfigManagement::checkSpace(std::string content) {
    int i = 0;

    if (content[i] == ' ') {
        while (content[i] == ' ') {
            i++;
        }
    } else {
        i = -1;
    }
    return (i);
}

std::string ConfigManagement::getKey(std::string content) {
    int begin = content.find("\"");
    int end = content.find("\"", begin + 1);

    if (begin != -1 && end != -1) {
        if (content[end + 1] == ':') {
            std::string subContent = content.substr(end);
            end = content.size() - begin - subContent.size();
            return (content.substr(begin, end + 1));
        }
    }

    return ("None");
}

std::string ConfigManagement::getArray(std::string content) {
    std::string subContent;
    int begin = content.find("[");
    int end = content.find("]", begin + 1);

    if (begin != -1 && end != -1) {
        std::string subContent = content.substr(end);
        end = content.size() - begin - subContent.size();
        return (content.substr(begin, end + 1));
    }
    return ("None");
}

std::string ConfigManagement::getDict(std::string content) {
    std::string subContent;
    int begin = content.find("{");
    int end = content.find("}", begin + 1);
    int count = 0;

    for (int i = begin; i != end; i++) {
        if (content[i] == '{')
            count++;
    }

    if (begin != -1 && end != -1 && count == 1) {
        subContent = content.substr(end);
        end = content.size() - begin - subContent.size();
        return (content.substr(begin, end + 1));
    } else if (begin != -1 && end != -1 && count > 1) {
        int i = begin;
        while (count != 0) {
            if (content[i] == '}') {
                end = i;
                count--;
            }
            i++;
        }
        subContent = content.substr(end);
        end = content.size() - begin - subContent.size();
        return (content.substr(begin, end + 1));
    }
    return ("None");
}

void ConfigManagement::parserServer() {
    std::string content = _fileContent.str();
    std::vector<std::string> info;
    std::string subContent;
    std::string key;
    std::string value;
    int space;
    int end;

    content = content.substr(content.find("server") - 1);
    content = getDict(content);

    while (content.size() > 1) {
        key = getKey(content);
        if (key != "None") {
            info.push_back(key);
            content = content.substr(content.find(key) + key.size() + 2);
            end = content.find("\n");
            if (end != -1 && content[end - 1] == ',') {
                subContent = content.substr(end);
                end = content.size() - subContent.size() - 1;
                value = content.substr(0, end);
            } else {
                subContent = content.substr(end);
                end = content.size() - subContent.size();
                value = content.substr(0, end);
            }
            info.push_back(value);
            _server.push_back(info);
            info.clear();
            content = content.substr(content.find("\n") + 1);
            space = checkSpace(content);
            content = content.substr(space);
        }
    }
}

void ConfigManagement::parserModules() {
    std::string content = _fileContent.str();
    std::vector<std::string> module;
    std::string subContent;
    std::string key;
    std::string value;
    int space;
    int end;

    content = content.substr(content.find("modules") - 1);
    content = getDict(content);

    while (content.size() > 1) {
        key = getKey(content);
        if (key != "None") {
            module.push_back(key);
            content = content.substr(content.find("path") + 7);
            subContent = content.substr(content.find("\n"));
            end = content.size() - subContent.size();
            value = content.substr(0, end);
            module.push_back(value);
            _modules.push_back(module);
            module.clear();
        }
        content = content.substr(content.find("\n") + 1);
        space = checkSpace(content);
        content = content.substr(space);
    }
}

Node ConfigManagement::buildNodeConfig() {
    Node obj;

    obj = Node::MakeDict({
        {"server", Node::MakeDict({
            {"ip", _server[0][1]},
            {"port", _server[1][1]},
            {"root", _server[2][1]}})},
        {"modules", Node::MakeDict({
            {"PHP", Node::MakeDict({
                {"path", _modules[0][1]}})},
            {"SSL", Node::MakeDict({
                {"path", _modules[1][1]}})}
            })
        }});
    return (obj);
}

