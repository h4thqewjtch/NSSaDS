#include "CloseCommand.h"

std::string CloseCommand::run_command(std::string &request) {
    request = "Session is closed";
    return request;
}
