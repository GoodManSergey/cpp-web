#include "ServerSocketLinux.h"
#include <bits/fcntl-linux.h>
#include <fcntl.h>
#include <unistd.h>


bool ServerSocketLinux::m_have_instance = false;


ResultCode ServerSocketLinux::init(int port)
{
    m_port = port;

    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) //TODO: choose INET family
    {
        //TODO: logs here
        return ResultCode::CREATE_SOCKET_FD_ERROR;
    }

    int flags;
    flags = fcntl(m_socket, F_GETFL, 0);
    if (flags == -1)
    {
        //TODO: logs here
        return ResultCode::NON_BLOCK_SET_SOCKET_ERROR;
    }
    fcntl(m_socket, F_SETFL, flags | O_NONBLOCK);

    m_address.sin_family = AF_INET;//TODO: choose family
    m_address.sin_port = htons(port);
    m_address.sin_addr.s_addr = INADDR_ANY;//TODO: choose mask

    int addr_size = sizeof(m_address);
    if (bind(m_socket, (sockaddr*)&m_address, (socklen_t)addr_size) < 0)
    {
        //TODO:Some logs here
        return ResultCode::BIND_SOCKET_ERROR;
    }

    return ResultCode::OK;
}

ServerSocketLinux::~ServerSocketLinux()
{
    close(m_socket);
}

Result<std::unique_ptr<ServerSocketLinux>> ServerSocketLinux::create(int port)
{
    if (ServerSocketLinux::m_have_instance)
    {
        return ResultCode::SERVER_SOCKET_ALREADY_STARTED;
    }

    struct ServerSocketLinuxFriend: public ServerSocketLinux{};
    std::unique_ptr<ServerSocketLinuxFriend> server_socket = std::make_unique<ServerSocketLinuxFriend>();
    auto init_result = server_socket->init(port);
    if (init_result == ResultCode::OK)
    {
        return std::move(Result<std::unique_ptr<ServerSocketLinux>>(std::move(server_socket)));
    }

    return init_result;
}