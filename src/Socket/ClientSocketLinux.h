#ifndef CPP_WEB_CLIENTSOCKETLINUX_H
#define CPP_WEB_CLIENTSOCKETLINUX_H

#include "../Utils/Result.h"
#include "../Request/RequestLine.h"
#include "../Request/Request.h"
#include "../Config/ConnectionConfig.h"
#include <string>
#include <memory>

class ClientSocketLinux {
public:
	ClientSocketLinux(int fd, ConnectionConfig config);
	~ClientSocketLinux();

	ResultCode get_request_line(Request& request);
	ResultCode get_request_headers(Request& request);
	ResultCode get_content(Request& request, unsigned long data_length);
	ResultCode send_response(const std::string& msg);

private:
	Result<std::string> read();
	Result<int> send(const std::string& msg);
	Result<std::string> read_http_part();

	ConnectionConfig m_config;

	int m_fd;
	std::string m_buffer;// TODO: ограничеие на буффер
	int m_send_current_pos;
};


#endif //CPP_WEB_CLIENTSOCKETLINUX_H
