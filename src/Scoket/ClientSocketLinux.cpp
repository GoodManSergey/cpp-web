#include "ClientSocketLinux.h"
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>


ClientSocketLinux::ClientSocketLinux(int fd):
    m_fd(fd)
{}

ClientSocketLinux::~ClientSocketLinux()
{
    close(m_fd);
}

void ClientSocketLinux::read()
{
    char buffer[1024];
    int msg_size;
    while (true)
    {
        msg_size =  ::recv(m_fd, buffer, 1024, MSG_DONTWAIT);
        std::cout<<msg_size<<std::endl;
        if ((errno == EAGAIN or errno == EWOULDBLOCK) and msg_size < 0)
        {
            msg_size =  ::recv(m_fd, buffer, 1024, 0);
            std::cout<<buffer<<std::endl;
            continue;
        }
        if (msg_size == 0)
        {
            break;
        }
        if (msg_size < 0)
            break;
        std::cout<<buffer<<std::endl;
    }

    std::cout<<msg_size;

}