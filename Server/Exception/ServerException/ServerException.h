#ifndef SERVER_SERVEREXCEPTION_H
#define SERVER_SERVEREXCEPTION_H

#include <iostream>
#include <exception>
#include <utility>

class ServerException : public std::exception {
private:
    const std::string exceptionInfo = "Something went wrong";
public:
    ServerException() = default;

    explicit ServerException(std::string exceptionInfo) :
            exceptionInfo(std::move(exceptionInfo)) {};

    virtual void print_exceptionInfo();
};


#endif //SERVER_SERVEREXCEPTION_H
