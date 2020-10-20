#ifndef CPP_WEB_HANDLERPOOLREGEXP_H
#define CPP_WEB_HANDLERPOOLREGEXP_H

#include "./HandlerPoolInterface.h"

class HandlerQueue {
public:
    Result<std::unique_ptr<Handler>> pop();
    void push_back(std::unique_ptr<Handler> handler);

private:
    std::mutex m_mutex;
    std::string m_path;
    std::deque<std::unique_ptr<Handler>> m_handlers;
};

class HandlerPoolRegexp: public HandlerPoolInterface {
public:
    Result<std::unique_ptr<Handler>> get_handler(const std::string &path) override;
    void return_handler(std::unique_ptr<Handler> handler) override;

private:
    std::unordered_map<std::string, HandlerQueue> m_handler_pool;
};

#endif //CPP_WEB_HANDLERPOOLREGEXP_H
