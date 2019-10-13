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

Result<std::unordered_map<std::string, std::string>> HTTPParser::parse_res_url(std::string& res_url)
{
    std::string res_url_with_args = res_url;
    int del_pos = res_url_with_args.find("?");
    if (del_pos == std::string::npos) {
        return std::move(Result<std::unordered_map<std::string, std::string>>({}));
    }

    res_url = res_url_with_args.substr(0, del_pos);
    res_url_with_args.erase(0, del_pos + 1);

    while ((del_pos = res_url_with_args.find("&")) != std::string::npos)
    {

    }

}