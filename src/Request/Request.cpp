#include "Request.h"

Method Request::get_request_method()
{
    return m_req_line.m_method;
}
