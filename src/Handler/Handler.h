#ifndef CPP_WEB_HANDLER_H
#define CPP_WEB_HANDLER_H

#include "../Request/Request.h"
#include "../Response/Response.h"
#include <memory>
#include <atomic>
#include <thread>

class Handler {
public:
	virtual Response get(const Request& request);
	virtual Response post(const Request& request);
	virtual Response put(const Request& request);
	virtual Response del(const Request& request);

	Response process_request(const Request& request);
};

#endif //CPP_WEB_HANDLER_H
