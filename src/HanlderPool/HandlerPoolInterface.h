#ifndef CPP_WEB_HANDLERPOOLINTERFACE_H
#define CPP_WEB_HANDLERPOOLINTERFACE_H

#include "../Handler/Handler.h"
#include "../Utils/Result.h"


class HandlerPoolInterface {
public:
    virtual ~HandlerPoolInterface() = 0;
    virtual Result<std::unique_ptr<Handler>> get_handler(const std::string& path) = 0;
    virtual void return_handler(std::unique_ptr<Handler> handler) = 0;
};


#endif //CPP_WEB_HANDLERPOOLINTERFACE_H
