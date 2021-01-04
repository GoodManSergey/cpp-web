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
		Response response;
		response.m_headers.insert({"Connection", "close"});
		response.m_code = StatusCode::S200;
		count++;
		std::cout << count << std::endl;
		return response;
	}

	static std::atomic<int> count;
};

std::atomic<int> HomeHandler::count = 0;

class TextHandler : public Handler {
public:
	explicit TextHandler(std::string text) :
		m_text(std::move(text)) {
	}

	Response get(const Request& request) override {
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
	//server.add_handler<TextHandler>(3, std::string("/text"), "some text here");
	server.add_handler<HomeHandler>(1000, std::string(".*"));

	std::cout << "http://127.0.0.1:" << 8080 << std::endl;

	while (true) {
		server.serve();
	}
}