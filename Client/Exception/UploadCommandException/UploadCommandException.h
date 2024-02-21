#ifndef CLIENT_UPLOADCOMMANDEXCEPTION_H
#define CLIENT_UPLOADCOMMANDEXCEPTION_H

#include "../ClientException/ClientException.h"

class UploadCommandException : public ClientException {
private:
    const std::string exceptionInfo = "UploadCommandException";
public:
    UploadCommandException() = default;

    explicit UploadCommandException(std::string exceptionInfo) :
            exceptionInfo(std::move(exceptionInfo)) {};

    void print_exceptionInfo() override;
};


#endif //CLIENT_UPLOADCOMMANDEXCEPTION_H
