#include "Server.h"
#include <unistd.h>
#include <iostream>

Server::Server(std::unique_ptr<ServerSocketLinux> server_socket, ServerConfig config) :
	m_config(std::move(config)),
	m_server_socket(std::move(server_socket)),
	m_active_connections(0)
{
	m_handlers = std::make_shared<std::vector<HandlerPool>>();
}

Server::~Server() {
	m_connections.clear();
}

void Server::serve() {
	auto result = m_server_socket->accept();
	if (result) {
		result.m_object->set_handlers(m_handlers);
		result.m_object->start();
		m_connections.push_front(std::move(result.m_object));
	}

	if (m_connections.empty()) {
		usleep(m_config.m_usleep_time_no_new_connections);
		return;
	}

	m_connections.remove_if([](std::unique_ptr<ClientConnection>& connection)
							{ return connection->get_state() == ClientConnection::State::SOCKET_CLOSED; });
}