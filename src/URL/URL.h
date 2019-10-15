#ifndef CPP_WEB_URL_H
#define CPP_WEB_URL_H

#include <list>
#include <unordered_map>
#include <string>

class URL
{
public:
    std::list<std::string> m_path;
    std::unordered_map<std::string, std::string> m_args;
};


#endif //CPP_WEB_URL_H
