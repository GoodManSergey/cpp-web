#ifndef CPP_WEB_HANDLERPOOL_H
#define CPP_WEB_HANDLERPOOL_H

#include <mutex>
#include <deque>
#include <string>
#include <memory>
#include "../Utils/Result.h"
#include "../Handler/Handler.h"

class HandlerPool {
public:
	HandlerPool() = default;
	explicit HandlerPool(std::string path);
	HandlerPool(HandlerPool&& other);
	void push_back(std::unique_ptr<Handler> handler);
	Result<std::unique_ptr<Handler>> get_handler();
	std::string get_path() const;

private:
	std::mutex m_mutex;
	std::string m_path;
	std::deque<std::unique_ptr<Handler>> m_handlers;
};


#endif //CPP_WEB_HANDLERPOOL_H
