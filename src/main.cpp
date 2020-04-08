#include "Socket/ServerSocketLinux.h"
#include "ClientConnection/ClientConnection.h"
#include "Utils/ResultCode.h"
#include <memory>
#include <iostream>

int main() {
	std::string msg{"HTTP/1.1 200 OK\r\n"
	                "Content-Length: 44\r\n"
	                "Connection: close\r\n"
	                "Content-Type: text/html\r\n"
	                "\r\n"
	                "<html><body><h1>It works!</h1></body></html>"};
	auto create_server_result = ServerSocketLinux::create(8080, ServerSocketLinux::SocketFamily::INET);
	if (!create_server_result) {
		std::cout << "Create server socket error" << std::endl;
		return -1;
	}
	std::unique_ptr<ServerSocketLinux> server(std::move(create_server_result.m_object));

	std::unique_ptr<ClientConnection> client;
	while (true) {
		auto accept_result = server->accept();
		if (accept_result) {
			client = std::move(accept_result.m_object);
			break;
		}
	}
	while (true) {
		auto rc = client->proceed();
		if (rc == ResultCode::REQUEST_READY)
			client->set_response(msg);
		if (rc == ResultCode::SOCKET_WAS_CLOSED)
			break;
	}
	return 0;
}