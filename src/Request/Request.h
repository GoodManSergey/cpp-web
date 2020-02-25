#ifndef CPP_WEB_REQUEST_H
#define CPP_WEB_REQUEST_H

#include <vector>
#include "RequestLine.h"
#include "../HTTP/Method.h"

class Request
{
public:
    explicit Request(const RequestLine& request_line) :
        m_request_line(request_line)
        { }

    Method get_request_method();

private:
    RequestLine m_request_line;
    std::vector<uint8_t> m_data;
    //TODO: Добавить поле headers

};


#endif //CPP_WEB_REQUEST_H
