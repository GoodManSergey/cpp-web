#include "Socket/ServerSocketLinux.h"
#include "ClientConnection/ClientConnection.h"
#include "ContentImpl/HTML/Html.h"
#include "Response/Response.h"
#include <memory>
#include <iostream>

int main() {
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
		if (rc == ResultCode::REQUEST_READY) {
			Response response;
			response.m_content = std::make_shared<Html>("<html><body><h1>It works!</h1></body></html>");
			client->set_response(response);
		}
		if (rc == ResultCode::SOCKET_WAS_CLOSED)
			break;
	}
	return 0;
}