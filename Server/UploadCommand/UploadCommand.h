#ifndef SERVER_UPLOADCOMMAND_H
#define SERVER_UPLOADCOMMAND_H

#include <fstream>
#include <vector>
#include <map>

#include "../Command/Command.h"
#include "../Exception/UploadCommandException/UploadCommandException.h"
#include "../Socket/Socket.h"

class UploadCommand : public Command {
private:
    static std::string filePath;
    static long long fileSize;

    static std::string get_currentFilePath_from_request(std::string &);

    static std::vector<std::string> split_string(std::string, char);

    static void upload_file();

    static void set_fileSize();

    static void send_fileSize();

    static void receive_fileSize();

    static void receive_file();

public:
    UploadCommand() = default;

    std::string run_command(std::string &) override;
};


#endif //SERVER_UPLOADCOMMAND_H
