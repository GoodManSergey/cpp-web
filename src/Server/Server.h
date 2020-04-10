#ifndef CPP_WEB_SERVER_H
#define CPP_WEB_SERVER_H

#include "../Socket/ServerSocketLinux.h"
#include "../ClientConnection/ClientConnection.h"
#include "../Handler/Handler.h"
#include "../Utils/AsyncForwardList.h"
#include <memory>
#include <atomic>
#include <vector>
#include <forward_list>
#include <thread>

class Server {
public:
	explicit Server(std::unique_ptr<ServerSocketLinux> server_socket);

	template <class Handler>
	void add_handler(int handlers_count);

	template <class Handler, class HandlerArgs>
	void add_handler(int handlers_count, HandlerArgs args);

	void serve();


private:
	std::atomic<bool> m_server_worker;

	std::unique_ptr<ServerSocketLinux> m_server_socket;

	std::vector<std::unique_ptr<Handler>> m_handlers;

	AsyncForwardList<std::unique_ptr<ClientConnection>> m_new_connections;
	std::forward_list<std::unique_ptr<ClientConnection>> m_connections;

};


#endif //CPP_WEB_SERVER_H
