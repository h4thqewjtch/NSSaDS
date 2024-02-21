#ifndef SERVER_CLOSECOMMAND_H
#define SERVER_CLOSECOMMAND_H

#include <iostream>
#include "../Command/Command.h"

class CloseCommand : public Command {
public:
    CloseCommand() = default;

    std::string run_command(std::string &) override;
};


#endif //SERVER_CLOSECOMMAND_H
