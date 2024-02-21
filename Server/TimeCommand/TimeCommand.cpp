#include "TimeCommand.h"

std::string TimeCommand::run_command(std::string& request) {
    long long seconds = what_time_is_it_now() - startTime;
    return "Server time is " + format_time(seconds);
}

long long TimeCommand::what_time_is_it_now() {
    auto now = std::chrono::system_clock::now();
    time_t now_c = std::chrono::system_clock::to_time_t(now);
    tm *currentTime = localtime(&now_c);
    return translate_to_seconds(currentTime);
}

long long TimeCommand::translate_to_seconds(tm *currentTime) {
    long long seconds = 3600 * (long long) currentTime->tm_hour;
    seconds += 60 * currentTime->tm_min;
    seconds += currentTime->tm_sec;
    seconds += 24 * 3600 * currentTime->tm_yday;
    return seconds;
}

std::string TimeCommand::format_time(long long &seconds) {
    std::string formattingTime;
    for (const auto &currentTimeFormat: timeFormats) {
        if (seconds >= currentTimeFormat.first) {
            formattingTime += translate_from_seconds(seconds, currentTimeFormat);
        }
    }
    return formattingTime;
}

std::string TimeCommand::translate_from_seconds(long long &seconds, const std::pair<long long, std::string> &format) {
    long long timeQuantity = seconds / format.first;
    seconds -= timeQuantity * format.first;
    return std::to_string(timeQuantity) + format.second;
}






