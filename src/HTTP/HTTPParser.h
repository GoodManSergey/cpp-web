#ifndef CPP_WEB_HTTPPARSER_H
#define CPP_WEB_HTTPPARSER_H

#include "../Request/RequestLine.h"
#include "../Utils/Result.h"
#include <string>
#include <unordered_map>

namespace HTTPParser
{
Result<RequestLine> parse_request_line(std::string data);
Result<std::unordered_map<std::string, std::string>> parse_res_url(std::string& res_url);
}

#endif //CPP_WEB_HTTPPARSER_H
