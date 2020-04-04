#include "Request.h"

Method Request::get_request_method() {
	return m_request_line.m_method;
}
