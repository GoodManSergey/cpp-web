#ifndef CPP_WEB_RESULT_H
#define CPP_WEB_RESULT_H

#include "ResultCode.h"

template <typename T>
struct Result
{
    result(result_code code):
            m_code(code)
    {}

    result(const T& object):
            m_code(result_code::OK),
            m_object(object)
    {}

    operator bool()
    {
        return m_code == result_code::OK;
    }

    result_code m_code;
    T m_object;
};

#endif //CPP_WEB_RESULT_H
