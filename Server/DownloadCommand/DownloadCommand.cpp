#include "DownloadCommand.h"

std::string DownloadCommand::filePath;
long long DownloadCommand::fileSize = 0;
long long DownloadCommand::filePosition = 0;

std::string DownloadCommand::run_command(std::string &request) {
    filePath = get_filePath_from_request(request);
    download_file();
    return "File downloaded";
}

std::string DownloadCommand::get_filePath_from_request(std::string &request) {
    std::vector<std::string> splitRequest = split_string(request, ' ');
    return splitRequest[1];
}

std::vector<std::string> DownloadCommand::split_string(std::string str, char separator) {
    std::vector<std::string> splitString{};
    size_t position;
    while ((position = str.find(separator)) != std::string::npos) {
        if (position) {
            std::string t = str.substr(0, position);
            splitString.push_back(t);
        }
        str.erase(0, position + 1);
    }
    splitString.push_back(str);
    return splitString;
}

void DownloadCommand::download_file() {
    filePosition = get_file_position();
    std::ifstream fileToDownload(filePath, std::ios::binary);
    if (!fileToDownload.is_open()) {
        send(Socket::get_connectedSocket(),
             "-1",
             sizeof("-1"),
             0);
        throw DownloadCommandException("Error opening file");
    }
    set_fileSize(fileToDownload);
    send_fileSize();
    if(filePosition!=fileSize) {
        Socket::set_socket_timeout(1000);
        Socket::clear_socket_buffer();
        send_file(fileToDownload);
    }
    fileToDownload.close();
}

long long DownloadCommand::get_file_position() {
    char buffer[1024];
    int receivedBytes = recv(Socket::get_connectedSocket(),
                             buffer,
                             sizeof(buffer),
                             0);
    std::string filePositionString = std::string(buffer);
    filePositionString = filePositionString.substr(0, receivedBytes);
    if (filePositionString.empty() || filePositionString == "-1") {
        throw DownloadCommandException("Error receiving file size");
    }
    return stoll(filePositionString);
}

void DownloadCommand::set_fileSize(std::ifstream &file) {
    file.seekg(0, std::ios::end);
    fileSize = (long long) file.tellg();
    file.seekg(filePosition, std::ios::beg);
}

void DownloadCommand::send_fileSize() {
    long long fileSizeToDownload = fileSize - filePosition;
    std::string fileSizeToDownloadString = std::to_string(fileSizeToDownload);
    int sentBytes = send(Socket::get_connectedSocket(),
                         fileSizeToDownloadString.c_str(),
                         (int) fileSizeToDownloadString.size(),
                         0);
    if (sentBytes == -1) {
        throw DownloadCommandException("Error sending file size");
    }
}

void DownloadCommand::send_file(std::ifstream &file) {
    char buffer[4];
    int totalSentBytes = 0;
    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        int readBytes = (int) file.gcount();
        int sentBytes = send(Socket::get_connectedSocket(),
                             buffer,
                             readBytes,
                             0);
        if (sentBytes == -1) {
            file.close();
            throw ServerException("File downloading failed");
        }
        totalSentBytes += sentBytes;
        std::cout << "Sent   :" << totalSentBytes * 100 / fileSize << "%" << std::endl;
    }
}
