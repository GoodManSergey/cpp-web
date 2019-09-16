#ifndef CPP_WEB_CLIENTSOCKETLINUX_H
#define CPP_WEB_CLIENTSOCKETLINUX_H

#include "../Utils/Result.h"
#include <memory>


class ClientSocketLinux {
public:
    static Result<std::unique_ptr<ClientSocketLinux>> create(int fd);
    ~ClientSocketLinux();

private:
    ClientSocketLinux(int fd);
    int m_fd;
};


#endif //CPP_WEB_CLIENTSOCKETLINUX_H
