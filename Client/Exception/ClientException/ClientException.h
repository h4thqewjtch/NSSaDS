#ifndef CLIENT_CLIENTEXCEPTION_H
#define CLIENT_CLIENTEXCEPTION_H

#include <iostream>
#include <exception>
#include <utility>

class ClientException : public std::exception {
    const std::string exceptionInfo = "Something went wrong";
public:
    ClientException() = default;

    explicit ClientException(std::string exceptionInfo) :
            exceptionInfo(std::move(exceptionInfo)) {};

    virtual void print_exceptionInfo();
};

#endif //CLIENT_CLIENTEXCEPTION_H
