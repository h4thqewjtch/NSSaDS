#include "UploadCommand.h"

std::string UploadCommand::filePath;
long long UploadCommand::fileSize = 0;

std::string UploadCommand::run_command(std::string &request) {
    filePath = get_currentFilePath_from_request(request);
    upload_file();
    return "File uploaded";
}

std::string UploadCommand::get_currentFilePath_from_request(std::string &request) {
    std::vector<std::string> splitRequest = split_string(request, ' ');
    return splitRequest[1];
}

std::vector<std::string> UploadCommand::split_string(std::string str, char separator) {
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

void UploadCommand::upload_file() {
    set_fileSize();
    send_fileSize();
    receive_fileSize();
    if(fileSize) {
        receive_file();
    }
}

void UploadCommand::set_fileSize() {
    std::ifstream fileToUpload(filePath, std::ios::binary);
    if (fileToUpload.is_open()) {
        fileToUpload.seekg(0, std::ios::end);
        fileSize = (long long) fileToUpload.tellg();
        fileToUpload.seekg(0, std::ios::beg);
        fileToUpload.close();
    }
}

void UploadCommand::send_fileSize() {
    std::string fileSizeString = std::to_string(fileSize);
    int sentBytes = send(Socket::get_connectedSocket(),
                         fileSizeString.c_str(),
                         (int) fileSizeString.size(),
                         0);
    if (sentBytes == -1) {
        throw UploadCommandException("Error sending file size");
    }
}

void UploadCommand::receive_fileSize() {
    char buffer[1024];
    int receivedBytes = recv(Socket::get_connectedSocket(),
                             buffer,
                             sizeof(buffer),
                             0);
    std::string fileSizeString = std::string(buffer);
    fileSizeString = fileSizeString.substr(0, receivedBytes);
    if (fileSizeString.empty() || fileSizeString == "-1") {
        throw UploadCommandException("Error receiving file size");
    }
    fileSize = stoll(fileSizeString);
}

void UploadCommand::receive_file() {
    std::ofstream fileToUpload(filePath, std::ios::binary | std::ios::app);
    if (!fileToUpload.is_open()) {
        throw UploadCommandException("Error opening file");
    }
    char buffer[4];
    while (fileSize > 0) {
        int receivedBytes = recv(Socket::get_connectedSocket(),
                                 buffer,
                                 (int) sizeof(buffer),
                                 0);
        if (receivedBytes == -1) {
            fileToUpload.close();
            throw ServerException("File uploading failed");
        }
        fileToUpload.write(buffer, receivedBytes);
        fileSize -= receivedBytes;
        std::cout << "Data to upload   :" << fileSize << std::endl;
    }
    fileToUpload.close();
}
