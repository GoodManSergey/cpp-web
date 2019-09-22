#ifndef CPP_WEB_HTTPPARSER_H
#define CPP_WEB_HTTPPARSER_H

#include "RequestLine.h"
#include "../Utils/Result.h"
#include <string>

namespace HTTPParser
{
Result<RequestLine> parse_request_line(std::string data);

}

#endif //CPP_WEB_HTTPPARSER_H
