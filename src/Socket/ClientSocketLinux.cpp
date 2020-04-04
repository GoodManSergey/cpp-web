#include "ClientSocketLinux.h"
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include "../HTTP/HttpParser.h"

ClientSocketLinux::ClientSocketLinux(int fd):
	m_fd(fd)
{ }

ClientSocketLinux::~ClientSocketLinux() {
	close(m_fd);
}

Result<std::string> ClientSocketLinux::read() {
	char buffer[1024];
	int msg_size;
	msg_size = ::recv(m_fd, buffer, 1024, MSG_DONTWAIT);

	if ((errno == EAGAIN || errno == EWOULDBLOCK) && msg_size < 0) {
		msg_size = ::recv(m_fd, buffer, 1024, 0);
	}

	if (msg_size > 0) {
		return std::move(Result<std::string>(std::move(std::string(buffer))));
	} else if (msg_size == 0) {
		return ResultCode::NOTHING_TO_READ;
	} else {
		return ResultCode::SOCKET_WAS_CLOSED;
	}
}

ResultCode ClientSocketLinux::send(std::string& msg) {
	int current_pos = 0;
	int rc = 0;

	//TODO:Добавить какой-то лимит на попытку отправки например, если мы несколько раз смогли отправить только 0 байт
	while (msg.length() != current_pos) {
		rc = ::send(m_fd, msg.c_str() + current_pos, msg.length() - current_pos, 0);

		if (rc < 0) {
			return ResultCode::SOCKET_WAS_CLOSED;
		} else if (rc > 0) {
			current_pos += rc;
		} else {
			//TODO: небольшой слип и счетчик обработчика
			}
	}

	return ResultCode::OK;
}

Result<RequestLine> ClientSocketLinux::get_request_line() {
	//TODO: ограничить попытки на читение, возможно таймер, чтобы не держать сокет, если соединение установили, но ничего не отправляют
	int pos = m_buffer.find("\r\n");

	if (pos != std::string::npos) {
		std::string result_string = m_buffer.substr(0, pos);
		m_buffer.erase(0, pos + 2);

		auto parse_result = HttpParser::parse_request_line(result_string);

		if (!parse_result) {
			return ResultCode::SOCKET_WAS_CLOSED;
		}

		return std::move(Result<RequestLine>(parse_result.m_object));
	} else {
		auto read_result = read();
		if (read_result) {
			m_buffer += read_result.m_object;

			return ResultCode::EMPTY_RESULT;
		} else {
			return read_result.m_code;
		}
	}
}

void ClientSocketLinux::test()
{
    std::string gotten;
    std::string msg{"HTTP/1.1 200 OK\r\n"
                    "Server: cpp-web 0.1v\n"
                    "Accept-Ranges: bytes\n"
                    "Content-Length: 44\n"
                    "Connection: close\n"
                    "Content-Type: text/html\n"
                    "\r\n"
                    "<html><body><h1>It works!</h1></body></html>"};
    while (true)
    {
        auto gotten_result = get_request_line();
        if (gotten_result)
        {
            std::cout<<gotten_result.m_object.m_path<<" "<<gotten_result.m_object.m_protocol_version<<std::endl;
            break;
        }
    }
    send(msg);
}