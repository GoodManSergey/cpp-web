#ifndef CPP_WEB_REQUEST_H
#define CPP_WEB_REQUEST_H

#include "RequestLine.h"
#include "../HTTP/Method.h"

class Request
{
public:
    Request(RequestLine req_line) : m_req_line(std::move(req_line)) { }
    Method get_request_method();

private:
    RequestLine m_req_line;
    //TODO: Поле data
    //TODO: Добавить поле headers

};


#endif //CPP_WEB_REQUEST_H
