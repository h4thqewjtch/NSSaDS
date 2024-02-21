#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

#include <iostream>

class Command {
public:
    Command() = default;
    virtual void run_command(std::string&) = 0;
};


#endif //CLIENT_COMMAND_H
