#ifndef CPP_WEB_REQUEST_H
#define CPP_WEB_REQUEST_H

#include <vector>
#include <unordered_map>
#include <string>
#include "RequestLine.h"
#include "../HTTP/Method.h"

class Request {
public:
	RequestLine m_request_line;
	std::vector<uint8_t> m_data;
	std::unordered_map<std::string, std::string> m_headers;
};


#endif //CPP_WEB_REQUEST_H
