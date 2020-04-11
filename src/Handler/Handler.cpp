#include "Handler.h"
#include <unistd.h>
#include <iostream>

Response Handler::get(Request request) {
	Response response;
	response.m_code = StatusCode::CE405;
	return response;
}

Response Handler::put(Request request) {
	Response response;
	response.m_code = StatusCode::CE405;
	return response;
}

Response Handler::post(Request request) {
	Response response;
	response.m_code = StatusCode::CE405;
	return response;
}

Response Handler::del(Request request) {
	Response response;
	response.m_code = StatusCode::CE405;
	return response;
}

void Handler::proceed() {
	while (m_handler_worker) {
		auto get_request_result = m_requests->front();
		if (get_request_result) {
			switch (get_request_result.m_object->m_request.m_request_line.m_method) {
				case Method::GET:
					get_request_result.m_object->set_response(get(get_request_result.m_object->m_request));
					break;
				case Method::POST:
					get_request_result.m_object->set_response(post(get_request_result.m_object->m_request));
					break;
				case Method::PUT:
					get_request_result.m_object->set_response(put(get_request_result.m_object->m_request));
					break;
				case Method::DELETE:
					get_request_result.m_object->set_response(del(get_request_result.m_object->m_request));
					break;
			}
			m_response_list->add(std::move(get_request_result.m_object));
		} else {
			usleep(200); // Todo: в конфиг
		}
	}
}

void Handler::start() {
	m_handler_worker = true;
	m_proceed_thread = std::thread(&Handler::proceed, this);
}

void Handler::stop() {
	m_handler_worker = false;
	m_proceed_thread.join();
}

void Handler::set_requests_queue(std::shared_ptr<AsyncQueue<std::unique_ptr<ClientConnection>>> requests_queue) {
	m_requests = std::move(requests_queue);
}

void Handler::set_response_list(std::shared_ptr<AsyncForwardList<std::unique_ptr<ClientConnection>>> response_list) {
	m_response_list = std::move(response_list);
}