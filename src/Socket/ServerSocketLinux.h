#ifndef CPP_WEB_SERVERSOCKETLINUX_H
#define CPP_WEB_SERVERSOCKETLINUX_H

#include "ClientSocketLinux.h"
#include "../ClientConnection/ClientConnection.h"
#include "../Utils/ResultCode.h"
#include "../Utils/Result.h"
#include "../Config/ConnectionConfig.h"
#include <csignal>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>

class ServerSocketLinux
{
public:

	enum class SocketFamily {
		INET,
	};

	static Result<std::unique_ptr<ServerSocketLinux>> create(int port, ServerSocketLinux::SocketFamily socket_family, ConnectionConfig config = ConnectionConfig());
	~ServerSocketLinux();

	Result<std::unique_ptr<ClientConnection>> accept();

private:
	static int get_socket_family(ServerSocketLinux::SocketFamily socket_family);
	ServerSocketLinux() = default;
	ResultCode init(int port, ServerSocketLinux::SocketFamily socket_family, ConnectionConfig config);

	ConnectionConfig m_config;

	static bool m_have_instance;

	int m_socket{};
	int m_port{};
	sockaddr_in m_address{};

};


#endif //CPP_WEB_SERVERSOCET_H
