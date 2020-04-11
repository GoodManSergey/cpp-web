#ifndef CPP_WEB_HANDLER_H
#define CPP_WEB_HANDLER_H

#include "../Request/Request.h"
#include "../Response/Response.h"
#include "../ClientConnection/ClientConnection.h"
#include "../Utils/AsyncForwardList.h"
#include "../Utils/AsyncQueue.h"
#include <memory>
#include <atomic>
#include <thread>

class Handler {
public:
	virtual Response get(Request request);
	virtual Response post(Request request);
	virtual Response put(Request request);
	virtual Response del(Request request);

	void set_requests_queue(std::shared_ptr<AsyncQueue<std::unique_ptr<ClientConnection>>> requests_queue);
	void set_response_list(std::shared_ptr<AsyncForwardList<std::unique_ptr<ClientConnection>>> response_list);
	void proceed();
	void start();
	void stop();

private:
	std::shared_ptr<AsyncQueue<std::unique_ptr<ClientConnection>>> m_requests;
	std::shared_ptr<AsyncForwardList<std::unique_ptr<ClientConnection>>> m_response_list;
	std::atomic<bool> m_handler_worker;

	std::thread m_proceed_thread;
};

#endif //CPP_WEB_HANDLER_H
