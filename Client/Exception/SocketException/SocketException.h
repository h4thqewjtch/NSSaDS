#ifndef CLIENT_SOCKETEXCEPTION_H
#define CLIENT_SOCKETEXCEPTION_H

#include "../ClientException/ClientException.h"

class SocketException : public ClientException {
private:
    const std::string exceptionInfo = "SocketException";
public:
    SocketException() = default;

    explicit SocketException(std::string exceptionInfo) :
            exceptionInfo(std::move(exceptionInfo)) {};

    void print_exceptionInfo() override;
};


#endif //CLIENT_SOCKETEXCEPTION_H
