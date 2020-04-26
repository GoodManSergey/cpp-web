#include "ServerSocketLinux.h"
#include <fcntl.h>
#include <unistd.h>

bool ServerSocketLinux::m_have_instance = false;

ResultCode ServerSocketLinux::init(int port, ServerSocketLinux::SocketFamily socket_family) {
	m_port = port;

	if ((m_socket = socket(get_socket_family(socket_family), SOCK_STREAM, 0)) == 0) {
		return ResultCode::CREATE_SOCKET_FD_ERROR;
	}

	int flags;
	flags = fcntl(m_socket, F_GETFL, 0);
	if (flags == -1) {
		return ResultCode::NON_BLOCK_SET_SOCKET_ERROR;
	}

	fcntl(m_socket, F_SETFL, flags | O_NONBLOCK);

	m_address.sin_family = get_socket_family(socket_family);
	m_address.sin_port = htons(port);
	m_address.sin_addr.s_addr = INADDR_ANY;

	int addr_size = sizeof(m_address);
	if (bind(m_socket, (sockaddr*)&m_address, (socklen_t)addr_size) < 0) {
		return ResultCode::BIND_SOCKET_ERROR;
	}

	if (listen(m_socket, 0) < 0) {
		return ResultCode::LISTEN_SOCKET_ERROR;
	}

	return ResultCode::OK;
}

ServerSocketLinux::~ServerSocketLinux() {
	close(m_socket);
	ServerSocketLinux::m_have_instance = false;
}

Result<std::unique_ptr<ServerSocketLinux>> ServerSocketLinux::create(int port, ServerSocketLinux::SocketFamily socket_family) {
	if (ServerSocketLinux::m_have_instance) {
		return ResultCode::SERVER_SOCKET_ALREADY_STARTED;
	}

	struct ServerSocketLinuxFriend: public ServerSocketLinux{};
	std::unique_ptr<ServerSocketLinuxFriend> server_socket = std::make_unique<ServerSocketLinuxFriend>();
	auto init_result = server_socket->init(port, socket_family);
	if (init_result == ResultCode::OK) {
		return std::move(Result<std::unique_ptr<ServerSocketLinux>>(std::move(server_socket)));
	}

	return init_result;
}

Result<std::unique_ptr<ClientConnection>> ServerSocketLinux::accept() {
	int addr_size = sizeof(m_address);
	int client_fd = ::accept(m_socket, (sockaddr*)&m_address, (socklen_t*)&addr_size);
	if (client_fd < 0) {
		return ResultCode::NO_NEW_CONNECTIONS;
	}

	std::unique_ptr<ClientSocketLinux> client_socket = std::make_unique<ClientSocketLinux>(client_fd);
	std::unique_ptr<ClientConnection> client_connection = std::make_unique<ClientConnection>(std::move(client_socket));

	return std::move(Result<std::unique_ptr<ClientConnection>>{std::move(client_connection)});
}

int ServerSocketLinux::get_socket_family(ServerSocketLinux::SocketFamily socket_family) {
	switch (socket_family) {
		case ServerSocketLinux::SocketFamily::INET:
			return AF_INET;
	}
}
