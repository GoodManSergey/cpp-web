#ifndef CPP_WEB_ASYNCQUEUE_H
#define CPP_WEB_ASYNCQUEUE_H

#include "Result.h"
#include <deque>
#include <mutex>
#include <memory>

template <class T>
class AsyncQueue {
public:
	void push_back(T element);
	Result<T> front();

private:
	std::deque<T> m_queue;
	std::mutex m_mutex;
};

template <class T>
void AsyncQueue<T>::push_back(T element) {
	const std::lock_guard<std::mutex> lock(m_mutex);
	m_queue.push_back(std::move(element));
}

template <class T>
Result<T> AsyncQueue<T>::front() {
	const std::lock_guard<std::mutex> lock(m_mutex);
	if (m_queue.size() == 0) {
		return ResultCode::EMPTY_RESULT;
	}
	auto element = std::move(m_queue.front());
	m_queue.pop_front();
	return Result<T>(std::move(element));
}

#endif //CPP_WEB_ASYNCQUEUE_H
