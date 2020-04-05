#ifndef CPP_WEB_CLIENTSOCKETLINUX_H
#define CPP_WEB_CLIENTSOCKETLINUX_H

#include "../Utils/Result.h"
#include "../Request/RequestLine.h"
#include "../Request/Request.h"
#include <string>
#include <memory>

class ClientSocketLinux {
public:
	explicit ClientSocketLinux(int fd);
	~ClientSocketLinux();

	ResultCode get_request_line(Request& request);
	ResultCode get_request_headers(Request& request);
	ResultCode get_content(Request& request, unsigned long data_length);

	void test();

private:
	Result<std::string> read();
	ResultCode send(std::string& msg);
	Result<std::string> read_http_part();

	int m_fd;
	std::string m_buffer;// TODO: ограничеие на буффер
};


#endif //CPP_WEB_CLIENTSOCKETLINUX_H
