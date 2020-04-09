#include "ClientConnection.h"

ClientConnection::ClientConnection(std::unique_ptr<ClientSocketLinux> client_socket) :
m_client_socket(std::move(client_socket)),
m_state(State::READ_REQUEST_LINE)
{ }

ResultCode ClientConnection::proceed() {
	switch (m_state) {
		case State::READ_REQUEST_LINE:
			return read_request_line();
		case State::READ_HEADERS:
			return read_headers();
		case State::READ_CONTENT:
			return read_content();
		case State::REQUEST_READY:
			return ResultCode::REQUEST_READY;
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
		m_state = State::READ_HEADERS;
		return ResultCode::CONTINUE;
	} else if (result == ResultCode::SOCKET_WAS_CLOSED) {
		m_state = State::SOCKET_CLOSED;
	}
	return result;
}

ResultCode ClientConnection::read_headers() {
	auto result = m_client_socket->get_request_headers(m_request);
	if (result == ResultCode::OK) {
		auto content_length_header = m_request.m_headers.find("Content-Length");
		if (content_length_header != m_request.m_headers.end()) {
			m_request.m_content_length = std::stoul(content_length_header->second);
			m_state = State::READ_CONTENT;
			return ResultCode::CONTINUE;
		} else {
			m_state = State::REQUEST_READY;
			return ResultCode::REQUEST_READY;
		}
	} else if (result == ResultCode::SOCKET_WAS_CLOSED) {
		m_state = State::SOCKET_CLOSED;
	}
	return result;
}

ResultCode ClientConnection::read_content() {
	auto result = m_client_socket->get_content(m_request, m_request.m_content_length);
	if (result == ResultCode::OK) {
		m_state = State::REQUEST_READY;
		return ResultCode::REQUEST_READY;
	} else if (result == ResultCode::SOCKET_WAS_CLOSED) {
		m_state = State::SOCKET_CLOSED;
	}
	return result;
}

ResultCode ClientConnection::send_response() {
	auto result = m_client_socket->send_response(m_response.serialize());
	if (result == ResultCode::OK) {
		//TODO: анализируем connectio и либо ставим статус read_request line либо socket close;
		m_state = State::SOCKET_CLOSED;
		return ResultCode::SOCKET_WAS_CLOSED;
	} else if (result == ResultCode::SOCKET_WAS_CLOSED) {
		m_state = State::SOCKET_CLOSED;
	}
	return result;
}

void ClientConnection::set_response(Response response) {
	m_state = State::SEND_RESPONSE;
	m_response = std::move(response);
}
