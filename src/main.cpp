#include "Socket/ServerSocketLinux.h"
#include "ClientConnection/ClientConnection.h"
#include "ContentImpl/HTML/Html.h"
#include "Handler/Handler.h"
#include "Server/Server.h"
#include <memory>
#include <iostream>

class HomeHandler : public Handler {
public:
	HomeHandler() = default;
	Response get(const Request& request) override {
		std::cout << "Start handle: " << request.m_request_line.m_path << std::endl;
		Response response;
		response.m_headers.insert({"Connection", "close"});
		response.m_headers.insert({"Location", "/text"});
		response.m_code = StatusCode::R301;
		return response;
	}
};

class TextHandler : public Handler {
public:
	explicit TextHandler(std::string text) :
		m_text(std::move(text)) {
	}

	Response get(const Request& request) override {
		std::cout << "Start handle: " << request.m_request_line.m_path << std::endl;
		Response response;
		response.m_content = std::make_shared<Html>(m_text);
		response.m_headers.insert({"Connection", "close"});
		return response;
	}

private:
	std::string m_text;
};

int main() {
	signal(SIGPIPE, SIG_IGN);
	auto create_server_result = ServerSocketLinux::create(8080, ServerSocketLinux::SocketFamily::INET);
	if (!create_server_result) {
		std::cout << "Create server socket error" << std::endl;
		return -1;
	}
	std::unique_ptr<ServerSocketLinux> server_socket(std::move(create_server_result.m_object));

	Server server(std::move(server_socket));
	server.add_handler<TextHandler>(3, std::string("/text"), "some text here");
	server.add_handler<HomeHandler>(3, std::string(".*"));

	std::cout << "http://127.0.0.1:" << 8080 << std::endl;

	while (true) {
		server.serve();
	}
}