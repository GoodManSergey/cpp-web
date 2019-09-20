#ifndef CPP_WEB_CLIENTSOCKETLINUX_H
#define CPP_WEB_CLIENTSOCKETLINUX_H

#include "../Utils/Result.h"
#include "../HTTP/RequestLine.h"
#include <string>
#include <memory>


class ClientSocketLinux
{
public:
    explicit ClientSocketLinux(int fd);
    Result<RequestLine> get_request_line();
    ~ClientSocketLinux();
    void test();

private:
    int m_fd;
    std::string m_buffer;// TODO: ограничеие на буффер
    Result<std::string> read();
    ResultCode send(std::string& msg);
};


#endif //CPP_WEB_CLIENTSOCKETLINUX_H
