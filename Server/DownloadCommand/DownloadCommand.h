#ifndef SERVER_DOWNLOADCOMMAND_H
#define SERVER_DOWNLOADCOMMAND_H

#include <fstream>
#include <vector>
#include <iomanip>

#include "../Command/Command.h"
#include "../Exception/DownloadCommandException/DownloadCommandException.h"
#include "../Socket/Socket.h"

class DownloadCommand : public Command {
private:
    static std::string filePath;
    static long long fileSize;
    static long long filePosition;

    static std::vector<std::string> split_string(std::string, char);

    static std::string get_filePath_from_request(std::string &);

    static void download_file();

    static long long get_file_position();

    static void set_fileSize(std::ifstream &);

    static void send_fileSize();

    static void send_file(std::ifstream &);

public:
    DownloadCommand() = default;

    std::string run_command(std::string &) override;
};


#endif //SERVER_DOWNLOADCOMMAND_H
