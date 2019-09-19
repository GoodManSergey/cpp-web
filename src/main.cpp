//
// Created by sergey on 16.09.19.
//

#include "Scoket/ServerSocketLinux.h"
#include "Scoket/ClientSocketLinux.h"
#include <memory>
#include <iostream>

int main()
{
    auto create_server_result = ServerSocketLinux::create(8080);
    if (!create_server_result)
    {
        std::cout << "Create server socket error" << std::endl;
        return -1;
    }
    std::unique_ptr<ServerSocketLinux> server(std::move(create_server_result.m_object));

    std::unique_ptr<ClientSocketLinux> client;
    while (true)
    {
        auto accept_result = server->accept();
        if (accept_result)
        {
            client = std::move(accept_result.m_object);
            break;
        }
    }
    client->test();
    return 0;
}