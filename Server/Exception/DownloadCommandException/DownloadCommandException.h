#ifndef SERVER_DOWNLOADCOMMANDEXCEPTION_H
#define SERVER_DOWNLOADCOMMANDEXCEPTION_H

#include "../ServerException/ServerException.h"

class DownloadCommandException : public ServerException {
private:
    const std::string exceptionInfo = "DownloadCommandException";
public:
    explicit DownloadCommandException(std::string exceptionInfo) :
            exceptionInfo(std::move(exceptionInfo)) {};

    void print_exceptionInfo() override;
};


#endif //SERVER_DOWNLOADCOMMANDEXCEPTION_H
