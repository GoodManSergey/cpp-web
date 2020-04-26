#include "HandlerPool.h"

HandlerPool::HandlerPool(std::string path) :
	m_path(std::move(path))
{ }

HandlerPool::HandlerPool(HandlerPool&& other) {
	m_path = std::move(other.m_path);
	while (auto res = other.get_handler()) {
		push_back(std::move(res.m_object));
	}
}

void HandlerPool::push_back(std::unique_ptr<Handler> handler) {
	std::lock_guard lock(m_mutex);
	m_handlers.push_back(std::move(handler));
}

Result<std::unique_ptr<Handler> > HandlerPool::get_handler() {
	std::lock_guard lock(m_mutex);
	if (m_handlers.empty()) {
		return ResultCode::EMPTY_RESULT;
	}
	auto handler = std::move(m_handlers.front());
	m_handlers.pop_front();
	return Result<std::unique_ptr<Handler>>(std::move(handler));
}

std::string HandlerPool::get_path() const {
	return m_path;
}
