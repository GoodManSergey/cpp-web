#ifndef CPP_WEB_RESULTCODE_H
#define CPP_WEB_RESULTCODE_H

enum class ResultCode: int
{
    //Success
    OK,

    //Socket errors
    CREATE_SOCKET_FD_ERROR,
    NON_BLOCK_SET_SOCKET_ERROR,
    BIND_SOCKET_ERROR
};
#endif //CPP_WEB_RESULTCODE_H
