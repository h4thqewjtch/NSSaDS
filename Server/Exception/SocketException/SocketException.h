#ifndef SERVER_SOCKETEXCEPTION_H
#define SERVER_SOCKETEXCEPTION_H

#include "../ServerException/ServerException.h"

class SocketException : public ServerException {
private:
    const std::string exceptionInfo = "SocketException";
public:
    SocketException() = default;

    explicit SocketException(std::string exceptionInfo) :
            exceptionInfo(std::move(exceptionInfo)) {};

    void print_exceptionInfo() override;
};


#endif //SERVER_SOCKETEXCEPTION_H
