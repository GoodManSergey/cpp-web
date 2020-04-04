#ifndef CPP_WEB_REQUESTLINE_H
#define CPP_WEB_REQUESTLINE_H

#include "../HTTP/Method.h"
#include <string>

class RequestLine {
public:
	RequestLine():
	m_method(Method::GET)
	{ }
	RequestLine(Method method, std::string path, std::string protocol_version):
	m_method(method),
	m_path(std::move(path)),
	m_protocol_version(std::move(protocol_version))
	{ }
	~RequestLine() = default;

	Method m_method;
	std::string m_path;
	std::string m_protocol_version;
};


#endif //CPP_WEB_REQUESTLINE_H
