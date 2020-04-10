#ifndef CPP_WEB_ASYNCFORWARDLIST_H
#define CPP_WEB_ASYNCFORWARDLIST_H

#include <forward_list>
#include <mutex>
#include <memory>

template <class T>
class AsyncForwardList {
public:
	void add(T element);
	std::forward_list<T> get_all();

private:
	std::forward_list<T> m_forward_list;
	std::mutex m_mutex;
};

template<class T>
void AsyncForwardList<T>::add(T element) {
	const std::lock_guard lock(m_mutex);
	m_forward_list.push_front(std::move(element));
}

template <class T>
std::forward_list<T> AsyncForwardList<T>::get_all() {
	const std::lock_guard lock(m_mutex);
	std::forward_list<T> new_forward_list(std::move(m_forward_list));
	m_forward_list = std::forward_list<T>();
	return new_forward_list;
}

#endif //CPP_WEB_ASYNCFORWARDLIST_H
