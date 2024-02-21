#include "DownloadCommand.h"

std::string DownloadCommand::filePath;
long long DownloadCommand::fileSize = 0;

void DownloadCommand::run_command(std::string &request) {
    filePath = get_filePath_from_request(request);
    download_file();
}

std::string DownloadCommand::get_filePath_from_request(std::string &request) {
    std::vector<std::string> splitRequest = split_string(request,(const std::string &) " ");
    return splitRequest[1];
}

std::vector<std::string> DownloadCommand::split_string(std::string str, const std::string &separator) {
    std::vector<std::string> splitString{};
    size_t position;
    while ((position = str.find(separator)) != std::string::npos) {
        if (position) {
            std::string t = str.substr(0,position);
            splitString.push_back(t);
        }
        str.erase(0, position + separator.length());
    }
    splitString.push_back(str);
    return splitString;
}

void DownloadCommand::download_file() {
    set_fileSize();
    send_fileSize();
    receive_fileSize();
    if(fileSize) {
        receive_file();
    }
}

void DownloadCommand::set_fileSize() {
    std::ifstream fileToDownload(filePath, std::ios::binary);
    if (fileToDownload.is_open()) {
        fileToDownload.seekg(0, std::ios::end);
        fileSize = (long long) fileToDownload.tellg();
        fileToDownload.seekg(0, std::ios::beg);
        fileToDownload.close();
    }
}

void DownloadCommand::send_fileSize() {
    std::string fileSizeString = std::to_string(fileSize);
    int sentBytes = send(Socket::get_createdSocket(),
                         fileSizeString.c_str(),
                         (int) fileSizeString.size(),
                         0);
    if (sentBytes == -1) {
        throw DownloadCommandException("Error sending file size");
    }
}

void DownloadCommand::receive_fileSize() {
    char buffer[1024];
    int receivedBytes = recv(Socket::get_createdSocket(),
                             buffer,
                             sizeof(buffer),
                             0);
    std::string fileSizeString = std::string(buffer);
    fileSizeString = fileSizeString.substr(0, receivedBytes);
    if (fileSizeString.empty() || fileSizeString == "-1") {
        throw DownloadCommandException("Error receiving file size");
    }
    fileSize = stoll(fileSizeString);
}

void DownloadCommand::receive_file() {
    std::ofstream fileToDownload(filePath,std::ios::binary | std::ios::app);
    if (!fileToDownload.is_open()) {
        throw DownloadCommandException("Error opening file");
    }
    char buffer[4];
    while (fileSize>0) {
        int receivedBytes = recv(Socket::get_createdSocket(),
                                 buffer,
                                 (int) sizeof(buffer),
                                 0);
        if (receivedBytes == -1) {
            fileToDownload.close();
            throw ClientException("File downloading failed");
        }
        fileToDownload.write(buffer, receivedBytes);
        fileSize -= receivedBytes;
        std::cout << " Data to download   :" << fileSize << std::endl;
    }
    fileToDownload.close();
}