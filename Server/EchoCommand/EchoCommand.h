#ifndef SERVER_ECHOCOMMAND_H
#define SERVER_ECHOCOMMAND_H

#include <iostream>
#include "../Command/Command.h"

class EchoCommand : public Command {
public:
    EchoCommand() = default;

    std::string run_command(std::string &) override;
};

#endif //SERVER_ECHOCOMMAND_H
