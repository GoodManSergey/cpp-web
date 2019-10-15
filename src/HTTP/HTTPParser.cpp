#include "HTTPParser.h"
#include "Method.h"
#include <iostream>
#include <unordered_map>
#include <list>


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
    if (method_string == "GET")
    {
        method = Method::GET;
    }
    else if (method_string == "PUT")
    {
        method = Method::PUT;
    }
    else if (method_string == "POST")
    {
        method = Method::POST;
    }
    else if (method_string == "DELETE")
    {
        method = Method::DELETE;
    }
    else
    {
        return ResultCode::PARSER_ERROR;
    }

    space_pos = data.find(" ");
    if (space_pos == std::string::npos)
    {
        return ResultCode::PARSER_ERROR;
    }

    std::string res_url = data.substr(0, space_pos);
    data.erase(0, space_pos + 1);

    return std::move(Result<RequestLine>(RequestLine(method, res_url, data)));
}

Result<URL> HTTPParser::parse_res_url(std::string res_url)
{
    URL url;

    int del_pos;
    while ((del_pos = res_url.rfind("/")) != std::string::npos)
    {
        std::string path = res_url.substr(del_pos, res_url.length());
        res_url.erase(del_pos, del_pos + path.length());
    }

    return std::move(Result<URL>(std::move(url)));
}
