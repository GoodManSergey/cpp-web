#ifndef CPP_WEB_HANDLER_H
#define CPP_WEB_HANDLER_H

#include "../Request/Request.h"
#include "../Response/Response.h"

class Handler {
public:
	virtual Response get();

};


#endif //CPP_WEB_HANDLER_H
