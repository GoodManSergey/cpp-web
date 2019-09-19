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

Result<std::string> ClientSocketLinux::read()
{
    char buffer[1024];
    int msg_size;
    msg_size = ::recv(m_fd, buffer, 1024, MSG_DONTWAIT);

    if ((errno == EAGAIN || errno == EWOULDBLOCK) && msg_size < 0)
    {
        msg_size = ::recv(m_fd, buffer, 1024, 0);
    }

    if (msg_size > 0)
    {
        return std::move(Result<std::string>(std::move(std::string(buffer))));
    }
    else if (msg_size == 0)
    {
        return ResultCode::NOTHING_TO_READ;
    }
    else
    {
        return ResultCode::SOCKET_WAS_CLOSED;
    }
}

ResultCode ClientSocketLinux::send(std::string& msg)
{
    int current_pos = 0;
    int rc = 0;

    //TODO:Добавить какой-то лимит на попытку отправки например, если мы несколько раз смогли отправить только 0 байт
    while (msg.length() != current_pos)
    {
        rc = ::send(m_fd, msg.c_str() + current_pos, msg.length() - current_pos, 0);

        if (rc < 0)
        {
            return ResultCode::SOCKET_WAS_CLOSED;
        }
        else if (rc > 0)
        {
            current_pos += rc;
        }
        else
        {
            //TODO: небольшой слип и счетчик обработчика
        }
    }

    return ResultCode::OK;
}

void ClientSocketLinux::test()
{
    std::string gotten;
    std::string msg{"HTTP/1.1 200 OK\r\n"
                    "Server: cpp-web 0.1v\n"
                    "Accept-Ranges: bytes\n"
                    "Content-Length: 44\n"
                    "Connection: close\n"
                    "Content-Type: text/html\n"
                    "\r\n"
                    "<html><body><h1>It works!</h1></body></html>"};
    while (true)
    {
        auto gotten_result = read();
        if (gotten_result)
        {
            std::cout<<gotten_result.m_object<<std::endl;
            break;
        }
    }
    send(msg);
}