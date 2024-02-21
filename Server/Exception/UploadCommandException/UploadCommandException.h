#ifndef SERVER_UPLOADCOMMANDEXCEPTION_H
#define SERVER_UPLOADCOMMANDEXCEPTION_H

#include "../ServerException/ServerException.h"

class UploadCommandException : public ServerException {
private:
    const std::string exceptionInfo = "UploadCommandException";
public:
    UploadCommandException() = default;

    explicit UploadCommandException(std::string exceptionInfo) :
            exceptionInfo(std::move(exceptionInfo)) {};

    void print_exceptionInfo() override;
};


#endif //SERVER_UPLOADCOMMANDEXCEPTION_H
