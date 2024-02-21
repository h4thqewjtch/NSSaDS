#ifndef SERVER_TIMECOMMAND_H
#define SERVER_TIMECOMMAND_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>

#include "../Command/Command.h"

class TimeCommand : public Command {
private:
    long long startTime{};
    std::vector<std::pair<long long, std::string>> timeFormats = {{31536000, " years "},
                                                                  {86400,    " days "},
                                                                  {3600,     " hours "},
                                                                  {60,       " minutes "},
                                                                  {1,        " seconds"}};

    static long long translate_to_seconds(tm *);

    std::string format_time(long long &);

    static std::string translate_from_seconds(long long &, const std::pair<long long, std::string> &);

public:
    TimeCommand() = default;

    explicit TimeCommand(long long startTime) {
        this->startTime = startTime;
    };

    static long long what_time_is_it_now();

    std::string run_command(std::string &) override;
};


#endif //SERVER_TIMECOMMAND_H
