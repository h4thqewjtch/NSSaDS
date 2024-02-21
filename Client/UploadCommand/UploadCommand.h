#ifndef CLIENT_UPLOADCOMMAND_H
#define CLIENT_UPLOADCOMMAND_H

#include <vector>
#include <fstream>
#include <iomanip>

#include "../Exception/UploadCommandException/UploadCommandException.h"
#include "../Command/Command.h"
#include "../Socket/Socket.h"

class UploadCommand : public Command {
private:
    static std::string filePath;
    static long long fileSize;
    static long long filePosition;

    static std::string get_filePath_from_request(std::string &);

    static std::vector<std::string> split_string(std::string, const std::string &);

    static void upload_file();

    static long long get_file_position();

    static void set_fileSize(std::ifstream &);

    static void send_fileSize();

    static void send_file(std::ifstream &);

public:
    UploadCommand() = default;

    void run_command(std::string &) override;
};


#endif //CLIENT_UPLOADCOMMAND_H
