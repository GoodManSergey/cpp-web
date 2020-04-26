#include "Handler.h"

Response Handler::get(const Request& request) {
	Response response;
	response.m_code = StatusCode::CE405;
	return response;
}

Response Handler::put(const Request& request) {
	Response response;
	response.m_code = StatusCode::CE405;
	return response;
}

Response Handler::post(const Request& request) {
	Response response;
	response.m_code = StatusCode::CE405;
	return response;
}

Response Handler::del(const Request& request) {
	Response response;
	response.m_code = StatusCode::CE405;
	return response;
}

Response Handler::process_request(const Request& request) {
	switch (request.m_request_line.m_method) {
		case Method::GET:
			return get(request);
		case Method::POST:
			return post(request);
		case Method::PUT:
			return put(request);
		case Method::DELETE:
			return del(request);
	}
}