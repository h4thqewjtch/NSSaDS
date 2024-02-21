#include "EchoCommand.h"

std::string EchoCommand::run_command(std::string &request) {
    request.erase(request.begin() + (int) request.find("echo"),
                  request.begin() + (int) request.find("echo") + 5);
    return request;
}
