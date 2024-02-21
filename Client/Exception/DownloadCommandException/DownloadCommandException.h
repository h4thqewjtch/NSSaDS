#ifndef CLIENT_DOWNLOADCOMMANDEXCEPTION_H
#define CLIENT_DOWNLOADCOMMANDEXCEPTION_H

#include "../ClientException/ClientException.h"

class DownloadCommandException : public ClientException {
private:
    const std::string exceptionInfo = "DownloadCommandException";
public:
    DownloadCommandException() = default;

    explicit DownloadCommandException(std::string exceptionInfo) :
            exceptionInfo(std::move(exceptionInfo)) {};

    void print_exceptionInfo() override;
};


#endif //CLIENT_DOWNLOADCOMMANDEXCEPTION_H
