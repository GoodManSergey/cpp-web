#ifndef CPP_WEB_HTTPPARSER_H
#define CPP_WEB_HTTPPARSER_H

#include "../Request/RequestLine.h"
#include "../Utils/Result.h"
#include <string>

namespace HttpParser {
	Result<RequestLine> parse_request_line(std::string data);
	Result<std::pair<std::string, std::string>> parse_header(std::string data);
}

#endif //CPP_WEB_HTTPPARSER_H
