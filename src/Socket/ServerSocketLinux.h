#ifndef CPP_WEB_SERVERSOCKETLINUX_H
#define CPP_WEB_SERVERSOCKETLINUX_H

#include "ClientSocketLinux.h"
#include "../Utils/ResultCode.h"
#include "../Utils/Result.h"
#include <csignal>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>

class ServerSocketLinux
{
public:
    static Result<std::unique_ptr<ServerSocketLinux>> create(int port);
    Result<std::unique_ptr<ClientSocketLinux>> accept();
    ~ServerSocketLinux();

private:
    ServerSocketLinux() = default;
    ResultCode init(int port);
    static bool m_have_instance;

    int m_socket{};
    int m_port{};
    sockaddr_in m_address{};

};


#endif //CPP_WEB_SERVERSOCET_H
