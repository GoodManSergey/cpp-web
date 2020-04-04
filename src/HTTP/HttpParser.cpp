#include "HttpParser.h"
#include "Method.h"
#include <iostream>
#include <unordered_map>
#include <list>

Result<RequestLine> HttpParser::parse_request_line(std::string data) {
	int space_pos = data.find(' ');
	if (space_pos == std::string::npos) {
		return ResultCode::PARSER_ERROR;
	}

	std::string method_string = data.substr(0, space_pos);
	data.erase(0, space_pos + 1);
	Method method;
	if (method_string == "GET") {
		method = Method::GET;
	} else if (method_string == "PUT") {
		method = Method::PUT;
	} else if (method_string == "POST") {
		method = Method::POST;
	} else if (method_string == "DELETE") {
		method = Method::DELETE;
	} else {
		return ResultCode::PARSER_ERROR;
	}

	space_pos = data.find(' ');
	if (space_pos == std::string::npos) {
		return ResultCode::PARSER_ERROR;
	}

	std::string res_url = data.substr(0, space_pos);
	data.erase(0, space_pos + 1);

	return std::move(Result<RequestLine>(RequestLine(method, res_url, data)));
}

Result<std::pair<std::string, std::string> > HttpParser::parse_header(std::string data) {
	int space_pos = data.find(": ");
	if (space_pos == std::string::npos) {
		return ResultCode::PARSER_ERROR;
	}
	return std::move(Result<std::pair<std::string, std::string>>({data.substr(0, space_pos), data.substr(space_pos + 2, data.length())}));
}
