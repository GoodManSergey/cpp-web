#include "ClientSocketLinux.h"
#include <unistd.h>
#include <sys/socket.h>
#include "../HTTP/HttpParser.h"

ClientSocketLinux::ClientSocketLinux(int fd):
	m_fd(fd),
	m_send_current_pos(0)
{ }

ClientSocketLinux::~ClientSocketLinux() {
	shutdown(m_fd, SHUT_RDWR);
	close(m_fd);
}

Result<std::string> ClientSocketLinux::read() {
	char buffer[1024];
	int msg_size;
	msg_size = ::recv(m_fd, buffer, 1024, MSG_DONTWAIT);

	if ((errno == EAGAIN || errno == EWOULDBLOCK) && msg_size < 0) {
		msg_size = ::recv(m_fd, buffer, 1024, 0);
	} else if (msg_size == 0) {
		return ResultCode::SOCKET_WAS_CLOSED;
	}
	if (msg_size > 0) {
		return std::move(Result<std::string>(std::move(std::string(buffer, msg_size))));
	} else if (msg_size == 0) {
		return ResultCode::NOTHING_TO_READ;
	} else {
		return ResultCode::SOCKET_WAS_CLOSED;
	}
}

Result<int> ClientSocketLinux::send(const std::string& msg) {
	int rc = 0;
	rc = ::send(m_fd, msg.c_str() + m_send_current_pos, msg.length() - m_send_current_pos, 0);
	if (rc < 0) {
		return ResultCode::SOCKET_WAS_CLOSED;
	} else {
		return Result<int>(rc);
	}
}

ResultCode ClientSocketLinux::get_request_line(Request& request) {
	auto read_result = read_http_part();
	if (read_result) {
		auto parse_result = HttpParser::parse_request_line(read_result.m_object);

		if (!parse_result) {
			return ResultCode::SOCKET_WAS_CLOSED;
		}

		request.m_request_line = parse_result.m_object;
		return ResultCode::OK;
	} else {
		return read_result.m_code;
	}
}

ResultCode ClientSocketLinux::get_request_headers(Request& request) {
	auto read_result = read_http_part();
	if (read_result.m_object.length() == 0) {
		return ResultCode::OK;
	}

	if (read_result) {
		auto parse_result = HttpParser::parse_header(read_result.m_object);

		if (!parse_result) {
			return ResultCode::SOCKET_WAS_CLOSED;
		}

		request.m_headers.insert(parse_result.m_object);
		return ResultCode::CONTINUE;
	}
	return read_result.m_code;
}

ResultCode ClientSocketLinux::get_content(Request &request, unsigned long content_length) {
	//TODO: ограничить попытки на читение, возможно таймер, чтобы не держать сокет, если соединение установили, но ничего не отправляют
	if (m_buffer.length() >= content_length) {
		std::string content = m_buffer.substr(0, content_length);
		m_buffer.erase(0, content_length);
		std::vector<uint8_t> content_vector{content.begin(), content.end()};
		request.m_content = std::move(content_vector);
		return ResultCode::OK;
	} else {
		auto read_result = read();
		if (read_result) {
			m_buffer += read_result.m_object;

			return ResultCode::CONTINUE;
		} else if (read_result.m_code == ResultCode::NOTHING_TO_READ) {
			return ResultCode::CONTINUE;
		} else {
			return read_result.m_code;
		}
	}
}

Result<std::string> ClientSocketLinux::read_http_part() {
	//TODO: ограничить попытки на читение, возможно таймер, чтобы не держать сокет, если соединение установили, но ничего не отправляют
	int pos = m_buffer.find("\r\n");

	if (pos != std::string::npos) {
		std::string result_string = m_buffer.substr(0, pos);
		m_buffer.erase(0, pos + 2);
		return std::move(Result<std::string>(result_string));
	} else {
		auto read_result = read();
		if (read_result) {
			m_buffer += read_result.m_object;

			return ResultCode::CONTINUE;
		} else if (read_result.m_code == ResultCode::NOTHING_TO_READ) {
			return ResultCode::CONTINUE;
		} else {
			return read_result.m_code;
		}
	}
}

ResultCode ClientSocketLinux::send_response(const std::string &msg) {
	//TODO:Добавить какой-то лимит на попытку отправки например, если мы несколько раз смогли отправить только 0 байт
	if (msg.length() != m_send_current_pos) {
		auto rc = send(msg.c_str() + m_send_current_pos);
		if (!rc) {
			return ResultCode::SOCKET_WAS_CLOSED;
		} else if (rc.m_object > 0) {
			m_send_current_pos += rc;
		} else {
			//Счетчик тут не смогли отправить больше
		}
	} else {
		m_send_current_pos = 0;
		return ResultCode::OK;
	}
	return ResultCode::CONTINUE;
}