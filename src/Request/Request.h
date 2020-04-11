#ifndef CPP_WEB_REQUEST_H
#define CPP_WEB_REQUEST_H

#include <vector>
#include <unordered_map>
#include <string>
#include <regex>
#include "RequestLine.h"
#include "../HTTP/Method.h"

class Request {
public:
	RequestLine m_request_line;
	std::vector<uint8_t> m_content;
	std::unordered_map<std::string, std::string> m_headers;
	unsigned long m_content_length;
	std::cmatch m_url_parse_result;
};


#endif //CPP_WEB_REQUEST_H
