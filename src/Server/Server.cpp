#include "Server.h"
#include <unistd.h>
#include <iostream>

Server::Server(std::unique_ptr<ServerSocketLinux> server_socket) :
m_server_worker(true),
m_server_socket(std::move(server_socket))
{
	m_handlers = std::make_shared<std::vector<HandlerPool>>();
}

void Server::serve() {
	while(m_server_worker) {
		auto result = m_server_socket->accept();
		if (result) {
			result.m_object->set_handlers(m_handlers);
			result.m_object->start();
			m_connections.push_front(std::move(result.m_object));
		}

		if (m_connections.empty()) {
			usleep(200); //TODO to config
			continue;
		}

		m_connections.remove_if([](std::unique_ptr<ClientConnection>& connection)
								{ return connection->get_state() == ClientConnection::State::SOCKET_CLOSED; });
	}

	m_connections.clear();
}

void Server::stop() {
	m_server_worker = false;
}