#include "HTTPParser.h"
#include "Method.h"
#include <iostream>


Result<RequestLine> HTTPParser::parse_request_line(std::string data)
{
    int space_pos = data.find(" ");
    if (space_pos == std::string::npos)
    {
        return ResultCode::PARSER_ERROR;
    }

    std::string method_string = data.substr(0, space_pos);
    data.erase(0, space_pos + 1);
    Method method;
    std::cout<<method_string<<std::endl;
    if (method_string == "GET")
    {
        method = Method::GET;
    }
    else
    {
        return ResultCode::PARSER_ERROR;
    }

    return std::move(Result<RequestLine>(RequestLine(method, "/", "HTTP 1.1")));
}
