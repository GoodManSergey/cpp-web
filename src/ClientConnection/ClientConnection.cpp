#include "ClientConnection.h"
#include <unistd.h>
#include <regex>
#include <cassert>
#include <iostream>

ClientConnection::ClientConnection(std::unique_ptr<ClientSocketLinux> client_socket, ConnectionConfig config) :
	m_config(std::move(config)),
	m_client_socket(std::move(client_socket)),
	m_state(State::READ_REQUEST_LINE),
	m_handlers(std::shared_ptr<std::vector<HandlerPool>>{})
{ }

ClientConnection::~ClientConnection() {
	stop();
}

void ClientConnection::set_handlers(std::shared_ptr<std::vector<HandlerPool>> handlers) {
	m_handlers = std::move(handlers);
}

ResultCode ClientConnection::proceed() {
	switch (m_state.load()) {
		case State::READ_REQUEST_LINE:
			return read_request_line();
		case State::READ_HEADERS:
			return read_headers();
		case State::READ_CONTENT:
			return read_content();
		case State::REQUEST_READY:
			return process_request();
		case State::SEND_RESPONSE:
			return send_response();
		case State::SOCKET_CLOSED:
		default:
			return ResultCode::SOCKET_WAS_CLOSED;
	}
}

ResultCode ClientConnection::read_request_line() {
	auto result = m_client_socket->get_request_line(m_request);
	if (result == ResultCode::OK) {
		m_state.store(State::READ_HEADERS);
		return ResultCode::CONTINUE;
	} else if (result == ResultCode::SOCKET_WAS_CLOSED) {
		m_state.store(State::SOCKET_CLOSED);
	}
	return result;
}

ResultCode ClientConnection::read_headers() {
	auto result = m_client_socket->get_request_headers(m_request);
	if (result == ResultCode::OK) {
		auto content_length_header = m_request.m_headers.find("Content-Length");
		if (content_length_header != m_request.m_headers.end()) {
			m_request.m_content_length = std::stoul(content_length_header->second);
			m_state.store(State::READ_CONTENT);
			return ResultCode::CONTINUE;
		} else {
			m_state.store(State::REQUEST_READY);
			return ResultCode::REQUEST_READY;
		}
	} else if (result == ResultCode::SOCKET_WAS_CLOSED) {
		m_state.store(State::SOCKET_CLOSED);
	}
	return result;
}

ResultCode ClientConnection::read_content() {
	auto result = m_client_socket->get_content(m_request, m_request.m_content_length);
	if (result == ResultCode::OK) {
		m_state.store(State::REQUEST_READY);
		return ResultCode::REQUEST_READY;
	} else if (result == ResultCode::SOCKET_WAS_CLOSED) {
		m_state.store(State::SOCKET_CLOSED);
	}
	return result;
}

ResultCode ClientConnection::process_request() {
	std::string path = m_request.m_request_line.m_path;
	for (auto& handler_pool : *m_handlers) {
		std::cmatch result;
		std::regex pattern(handler_pool.get_path().c_str());
		if (std::regex_match(path.c_str(), result, pattern)) {
			m_request.m_url_parse_result = std::move(result);
			while (m_state.load() != State::SOCKET_CLOSED) { //TODO: oграничить кол-во попыток
				auto get_handler_result = handler_pool.get_handler();
				if (get_handler_result) {
					std::unique_ptr<Handler> handler = std::move(get_handler_result.m_object);
					m_response = handler->process_request(m_request);
					m_state.store(State::SEND_RESPONSE);
					handler_pool.push_back(std::move(handler));
					return ResultCode::OK;
				} else {
					usleep(m_config.m_usleep_time_no_free_handler);
				}
			}
		}
	}
	if (m_state.load() == State::SOCKET_CLOSED) {
		return ResultCode::OK;
	}
	assert(false);
}

ResultCode ClientConnection::send_response() {
	auto result = m_client_socket->send_response(m_response.serialize()); // ToDO: делать serialize 1 раз и хранить его результат
	if (result == ResultCode::OK) {
		//TODO: анализируем connectio и либо ставим статус read_request line либо socket close;
		m_state.store(State::SOCKET_CLOSED);
		return ResultCode::SOCKET_WAS_CLOSED;
	} else if (result == ResultCode::SOCKET_WAS_CLOSED) {
		m_state.store(State::SOCKET_CLOSED);
	}
	return result;
}

ClientConnection::State ClientConnection::get_state() {
	auto state = m_state.load();
	return state;
}

void ClientConnection::proceed_func() {
	while (m_state.load() != State::SOCKET_CLOSED) {
		auto result = proceed();
		if (result == ResultCode::NOTHING_TO_READ) {
			usleep(m_config.m_usleep_time_nothing_to_read);
		}
	}
}

void ClientConnection::start() {
	assert(m_handlers);
	m_proceed_thread = std::thread(&ClientConnection::proceed_func, this);
}

void ClientConnection::stop() {
	m_state.store(State::SOCKET_CLOSED);
	m_proceed_thread.join();
}