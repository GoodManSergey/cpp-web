#ifndef CPP_WEB_CLIENTSOCKETLINUX_H
#define CPP_WEB_CLIENTSOCKETLINUX_H

#include "../Utils/Result.h"
#include <string>
#include <memory>


class ClientSocketLinux
{
public:
    explicit ClientSocketLinux(int fd);
    ~ClientSocketLinux();
    void test();

private:
    int m_fd;
    Result<std::string> read();
    ResultCode send(std::string& msg);
};


#endif //CPP_WEB_CLIENTSOCKETLINUX_H
