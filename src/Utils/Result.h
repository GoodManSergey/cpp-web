#ifndef CPP_WEB_RESULT_H
#define CPP_WEB_RESULT_H

#include "ResultCode.h"

template <typename T>
struct Result
{
    Result(ResultCode code):
            m_code(code)
    {}

    Result(const T& object):
            m_code(ResultCode::OK),
            m_object(object)
    {}

    operator bool()
    {
        return m_code == ResultCode::OK;
    }

    ResultCode m_code;
    T m_object;
};

#endif //CPP_WEB_RESULT_H
