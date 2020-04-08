#ifndef CPP_WEB_CLIENTCONNECTION_H
#define CPP_WEB_CLIENTCONNECTION_H

#include "../Socket/ClientSocketLinux.h"
#include "../Utils/ResultCode.h"
#include "../Request/Request.h"
#include <memory>

class ClientConnection {
public:
	enum class State {
		READ_REQUEST_LINE,
		READ_HEADERS,
		READ_CONTENT,
		REQUEST_READY,
		SEND_RESPONSE,
		SOCKET_CLOSED
	};

	explicit ClientConnection(std::unique_ptr<ClientSocketLinux> client_socket);
	ResultCode proceed();
	void set_response(const std::string& response);

private:
	ResultCode read_request_line();
	ResultCode read_headers();
	ResultCode read_content();

	ResultCode send_response();

	std::unique_ptr<ClientSocketLinux> m_client_socket;
	State m_state;
	Request m_request;
	std::string m_response; // заменить на класс
};


#endif //CPP_WEB_CLIENTCONNECTION_H
