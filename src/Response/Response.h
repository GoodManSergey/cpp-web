#ifndef CPP_WEB_RESPONSE_H
#define CPP_WEB_RESPONSE_H

#include "../Content/Content.h"
#include "../HTTP/Status.h"
#include <memory>
#include <unordered_map>

class Response {
public:
	Response();
	std::string serialize();

	StatusCode m_code;
	std::unordered_map<std::string, std::string> m_headers;
	std::shared_ptr<Content> m_content;
};


#endif //CPP_WEB_RESPONSE_H
