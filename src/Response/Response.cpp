#include "Response.h"
#include <sstream>

Response::Response() :
m_code(StatusCode::S200)
{ }

std::string Response::serialize() {
	std::stringstream ss;
	ss << "HTTP/1.1 ";
	ss << get_status_code_description(m_code);
	ss << "\r\n";

	for (auto & header : m_headers) {
		ss << header.first;
		ss << ": ";
		ss << header.second;
		ss << "\r\n";
	}

	if (m_content) {
		ss << "Content-Length: " << m_content->get_content_length() << "\r\n";
		ss << "Content-Type: " << m_content->get_content_type() << "\r\n";
		ss << "\r\n";
		ss << m_content->serialize();
	} else {
		ss << "\r\n";
	}

	return ss.str();
}