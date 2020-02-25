#ifndef CPP_WEB_URL_H
#define CPP_WEB_URL_H

#include <unordered_map>
#include <string>
#include <regex>

class URL
{
public:
    explicit URL(std::string path) :
        m_path(std::move(path))
    { }

    std::string m_path;
    std::unordered_map<std::string, std::string> m_args;
    std::smatch m_template_args;
};


#endif //CPP_WEB_URL_H
