#ifndef CPP_WEB_HTTPPARSER_H
#define CPP_WEB_HTTPPARSER_H

#include "../Request/RequestLine.h"
#include "../Utils/Result.h"
#include "../URL/URL.h"
#include <string>

namespace HTTPParser
{
Result<RequestLine> parse_request_line(std::string data);
//Result<URL> parse_res_url(std::string res_url);
}

#endif //CPP_WEB_HTTPPARSER_H
