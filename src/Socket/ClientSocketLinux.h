#ifndef CPP_WEB_CLIENTSOCKETLINUX_H
#define CPP_WEB_CLIENTSOCKETLINUX_H

#include "../Utils/Result.h"
#include "../Request/RequestLine.h"
#include <string>
#include <memory>

class ClientSocketLinux
{
public:
	explicit ClientSocketLinux(int fd);
	~ClientSocketLinux();

	Result<RequestLine> get_request_line();
	void test();

private:
	Result<std::string> read();
	ResultCode send(std::string& msg);

	int m_fd;
	std::string m_buffer;// TODO: ограничеие на буффер
};


#endif //CPP_WEB_CLIENTSOCKETLINUX_H
