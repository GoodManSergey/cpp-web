#include "ServerSocketLinux.h"
#include <bits/fcntl-linux.h>
#include <fcntl.h>
#include <netinet/in.h>


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

    sockaddr_in  address{};//TODO: choose INET family

    address.sin_family = AF_INET;//TODO: choose family
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;//TODO: choose mask

    int addr_size = sizeof(address);
    if (bind(m_socket, (sockaddr*)&address, (socklen_t)addr_size) < 0)
    {
        //TODO:Some logs here
        return ResultCode::BIND_SOCKET_ERROR;
    }

    return ResultCode::OK;
}