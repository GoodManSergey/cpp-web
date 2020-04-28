#ifndef CPP_WEB_SERVER_H
#define CPP_WEB_SERVER_H

#include "../Socket/ServerSocketLinux.h"
#include "../ClientConnection/ClientConnection.h"
#include "../Handler/Handler.h"
#include "../HanlderPool/HandlerPool.h"
#include <memory>
#include <atomic>
#include <vector>
#include <forward_list>
#include <thread>
#include <deque>
#include <regex>
#include <iostream>

class Server {
public:
	explicit Server(std::unique_ptr<ServerSocketLinux> server_socket);
	~Server();

	template <class Handler>
	void add_handler(int handlers_count, std::string handler_regexp);
	void serve();

private:
	std::unique_ptr<ServerSocketLinux> m_server_socket;

	std::shared_ptr<std::vector<HandlerPool>> m_handlers;

	std::forward_list<std::unique_ptr<ClientConnection>> m_connections;
};

template<class Handler>
void Server::add_handler(int handlers_count, std::string handler_regexp) {
	HandlerPool handler_pool(std::move(handler_regexp));
	for (int i = 0; i < handlers_count; i++) {
		auto handler = std::make_unique<Handler>();
		handler_pool.push_back(std::move(handler));
	}
	m_handlers->push_back(std::move(handler_pool));
}

#endif //CPP_WEB_SERVER_H
