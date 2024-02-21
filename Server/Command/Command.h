#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <iostream>

class Command {
public:
    Command() = default;

    virtual std::string run_command(std::string &) = 0;
};

#endif //SERVER_COMMAND_H
