#ifndef CPP_WEB_CLIENTSOCKETLINUX_H
#define CPP_WEB_CLIENTSOCKETLINUX_H

#include "../Utils/Result.h"
#include <memory>


class ClientSocketLinux
{
public:
    explicit ClientSocketLinux(int fd);
    void read();
    ~ClientSocketLinux();

private:
    int m_fd;
};


#endif //CPP_WEB_CLIENTSOCKETLINUX_H
