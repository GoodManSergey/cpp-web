#include "Handler.h"

Response Handler::get() {
	Response response;
	response.m_code = StatusCode::CE405;
	return response;
}

void Handler::start() {
	return;
}

void Handler::stop() {
	return;
}