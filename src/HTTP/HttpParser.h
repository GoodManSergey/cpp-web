#ifndef CPP_WEB_HTTPPARSER_H
#define CPP_WEB_HTTPPARSER_H

#include "../Request/RequestLine.h"
#include "../Utils/Result.h"
#include "../URL/URL.h"
#include <string>

namespace HttpParser {
Result<RequestLine> parse_request_line(std::string data);
}

#endif //CPP_WEB_HTTPPARSER_H
