#include "Server.h"
#include <unistd.h>
#include <iostream>

Server::Server(std::unique_ptr<ServerSocketLinux> server_socket) :
m_server_worker(true),
m_server_socket(std::move(server_socket)),
m_new_connections(std::make_shared<AsyncForwardList<std::unique_ptr<ClientConnection>>>())
{ }

void Server::get_new_connections() {
	while (m_server_worker) {
		auto result = m_server_socket->accept();
		if (result) {
			m_new_connections->add(std::move(result.m_object));
		} else {
			usleep(10); // TODO: в конфиг
		}
	}
}

void Server::put_request_to_handler(std::unique_ptr<ClientConnection> request) {
	for (auto & handler : m_ready_requests) {
		std::regex re(handler.first);
		std::cmatch parse_result;
		bool result = std::regex_match(request->m_request.m_request_line.m_path.c_str(), parse_result, re);

		if (result) {
			request->m_request.m_url_parse_result = std::move(parse_result);
			handler.second->push_back(std::move(request));
			break;
		} else {
			continue;
		}
	}
}

void Server::serve() {
	m_accept_new_connections_thread = std::thread(&Server::get_new_connections, this);

	for (auto & handler : m_handlers) {
		handler->start();
	}

	while(m_server_worker) {
		m_connections = std::forward_list<std::unique_ptr<ClientConnection>>();
		m_connections.merge(std::move(m_new_connections->get_all()));

		for (auto && connection : m_connections) {
			auto result = connection->proceed();

			if (result == ResultCode::CONTINUE) {
				m_new_connections->add(std::move(connection));
				continue;
			} else if (result == ResultCode::REQUEST_READY) {
				put_request_to_handler(std::move(connection));
			} else {
				continue;
			}
		}
	}

	for (auto & handler : m_handlers) {
		handler->stop();
	}

	m_accept_new_connections_thread.join();
}

void Server::stop() {
	m_server_worker = false;
}