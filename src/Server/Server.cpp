#include "Server.h"
#include "../Utils/ResultCode.h"

Server::Server(std::unique_ptr<ServerSocketLinux> server_socket) :
m_server_worker(true),
m_server_socket(std::move(server_socket))
{ }

template<class Handler>
void Server::add_handler(int handlers_count) {
	for (int i = 0; i < handlers_count; i++) {
		m_handlers.push_back(std::make_unique<Handler>());
	}
}

template<class Handler, class HandlerArgs>
void Server::add_handler(int handlers_count, HandlerArgs args) {
	for (int i = 0; i < handlers_count; i++) {
		m_handlers.push_back(std::unique_ptr<Handler>(args));
	}
}

void Server::serve() {
	for (auto & handler : m_handlers) {
		handler->start();
	}

	while(m_server_worker) {
		m_connections = std::forward_list<std::unique_ptr<ClientConnection>>();
		m_connections.merge(std::move(m_new_connections.get_all()));

		for (auto && connection : m_connections) {
			auto result = connection->proceed();

			if (result == ResultCode::CONTINUE) {
				m_new_connections.add(std::move(connection));
				continue;
			} else if (result == ResultCode::REQUEST_READY) {
				// ToDo: отдаем в handler;
			} else {
				continue;
			}
		}
	}

	for (auto & handler : m_handlers) {
		handler->stop();
	}
}