#include "Socket/ServerSocketLinux.h"
#include "ClientConnection/ClientConnection.h"
#include "ContentImpl/HTML/Html.h"
#include "Handler/Handler.h"
#include "Server/Server.h"
#include <memory>
#include <iostream>

class HomeHandler : public Handler {
	Response get(Request request) override {
		Response response;
		response.m_content = std::make_shared<Html>(request.m_request_line.m_path);
		return response;
	}
};

int main() {
	auto create_server_result = ServerSocketLinux::create(8080, ServerSocketLinux::SocketFamily::INET);
	if (!create_server_result) {
		std::cout << "Create server socket error" << std::endl;
		return -1;
	}
	std::unique_ptr<ServerSocketLinux> server_socket(std::move(create_server_result.m_object));

	Server server(std::move(server_socket));
	server.add_handler<HomeHandler>(1, ".*");
	server.serve();

}