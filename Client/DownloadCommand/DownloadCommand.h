#ifndef CLIENT_DOWNLOADCOMMAND_H
#define CLIENT_DOWNLOADCOMMAND_H

#include <fstream>
#include <vector>
#include <map>

#include "../Exception/DownloadCommandException/DownloadCommandException.h"
#include "../Command/Command.h"
#include "../Socket/Socket.h"

class DownloadCommand : public Command {
private:
    static std::string filePath;
    static long long fileSize;

    static std::string get_filePath_from_request(std::string &);

    static std::vector<std::string> split_string(std::string, const std::string &);

    static void download_file();

    static void set_fileSize();

    static void send_fileSize();

    static void receive_fileSize();

    static void receive_file();

public:
    DownloadCommand() = default;

    void run_command(std::string &) override;
};


#endif //CLIENT_DOWNLOADCOMMAND_H
