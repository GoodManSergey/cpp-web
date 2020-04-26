#ifndef CPP_WEB_CLIENTCONNECTION_H
#define CPP_WEB_CLIENTCONNECTION_H

#include "../Socket/ClientSocketLinux.h"
#include "../Utils/ResultCode.h"
#include "../Request/Request.h"
#include "../Response/Response.h"
#include "../Handler/Handler.h"
#include "../HanlderPool/HandlerPool.h"
#include <memory>
#include <atomic>
#include <thread>

class ClientConnection {
public:
	enum class State: int {
		READ_REQUEST_LINE,
		READ_HEADERS,
		READ_CONTENT,
		REQUEST_READY,
		SEND_RESPONSE,
		SOCKET_CLOSED
	};

	explicit ClientConnection(std::unique_ptr<ClientSocketLinux> client_socket);
	~ClientConnection();
	void set_handlers(std::shared_ptr<std::vector<HandlerPool>> handlers);
	void start();
	void stop();
	State get_state();

private:
	void proceed_func();

	ResultCode proceed();

	ResultCode read_request_line();
	ResultCode read_headers();
	ResultCode read_content();
	ResultCode process_request();
	ResultCode send_response();

	std::thread m_proceed_thread;

	Request m_request;
	Response m_response;

	std::unique_ptr<ClientSocketLinux> m_client_socket;
	std::atomic<State> m_state;
	std::shared_ptr<std::vector<HandlerPool>> m_handlers;
};


#endif //CPP_WEB_CLIENTCONNECTION_H
