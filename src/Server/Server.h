#ifndef CPP_WEB_SERVER_H
#define CPP_WEB_SERVER_H

#include "../Socket/ServerSocketLinux.h"
#include "../ClientConnection/ClientConnection.h"
#include "../Handler/Handler.h"
#include "../Utils/AsyncForwardList.h"
#include "../Utils/AsyncQueue.h"
#include <memory>
#include <atomic>
#include <vector>
#include <forward_list>
#include <thread>
#include <deque>
#include <regex>

class Server {
public:
	explicit Server(std::unique_ptr<ServerSocketLinux> server_socket);

	template <class Handler>
	void add_handler(int handlers_count, const std::string& handler_regexp);
	template <class Handler, class HandlerArgs>
	void add_handler(int handlers_count, HandlerArgs args, const std::string& handler_regexp);
	void get_new_connections();
	void serve();
	void stop();


private:
	void put_request_to_handler(std::unique_ptr<ClientConnection> request);

	std::atomic<bool> m_server_worker;

	std::unique_ptr<ServerSocketLinux> m_server_socket;

	std::vector<std::unique_ptr<Handler>> m_handlers;

	std::vector<std::pair<std::string, std::shared_ptr<AsyncQueue<std::unique_ptr<ClientConnection>>>>> m_ready_requests;

	std::shared_ptr<AsyncForwardList<std::unique_ptr<ClientConnection>>> m_new_connections;
	std::forward_list<std::unique_ptr<ClientConnection>> m_connections;

	std::thread m_accept_new_connections_thread;
};


#endif //CPP_WEB_SERVER_H
