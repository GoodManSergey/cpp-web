#ifndef CPP_WEB_METHOD_H
#define CPP_WEB_METHOD_H

#include <string>

enum class Method: int
{
    GET,
    POST,
    PUT,
    DELETE
};

std::string method_to_string(Method method)
{
    switch (method)
    {
        case Method::GET:
            return "GET";
        case Method::POST:
            return "POST"
    }
}

#endif //CPP_WEB_METHOD_H
