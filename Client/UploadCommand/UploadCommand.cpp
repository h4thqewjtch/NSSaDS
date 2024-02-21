#include "UploadCommand.h"

std::string UploadCommand::filePath;
long long UploadCommand::fileSize = 0;
long long UploadCommand::filePosition = 0;

void UploadCommand::run_command(std::string &request) {
    filePath = get_filePath_from_request(request);
    upload_file();
}

std::string UploadCommand::get_filePath_from_request(std::string &request) {
    std::vector<std::string> splitRequest = split_string(request, (const std::string &) " ");
    return splitRequest[1];
}

std::vector<std::string> UploadCommand::split_string(std::string str, const std::string &separator) {
    std::vector<std::string> splitString{};
    size_t position;
    while ((position = str.find(separator)) != std::string::npos) {
        if (position) {
            std::string t = str.substr(0, position);
            splitString.push_back(t);
        }
        str.erase(0, position + separator.length());
    }
    splitString.push_back(str);
    return splitString;
}

void UploadCommand::upload_file() {
    filePosition = get_file_position();
    std::ifstream fileToUpload(filePath, std::ios::binary);
    if (!fileToUpload.is_open()) {
        send(Socket::get_createdSocket(),
             "-1",
             sizeof("-1"),
             0);
        throw UploadCommandException("Error opening file");
    }
    set_fileSize(fileToUpload);
    send_fileSize();
    if(filePosition!=fileSize) {
        Socket::set_socket_timeout(1000);
        Socket::clear_socket_buffer();
        send_file(fileToUpload);
    }
    fileToUpload.close();
}

long long UploadCommand::get_file_position(){
    char buffer[1024];
    int receivedBytes = recv(Socket::get_createdSocket(),
                             buffer,
                             sizeof(buffer),
                             0);
    std::string filePositionString = std::string(buffer);
    filePositionString = filePositionString.substr(0, receivedBytes);
    if (filePositionString.empty() || filePositionString == "-1") {
        throw UploadCommandException("Error receiving file size");
    }
    return stoll(filePositionString);
}

void UploadCommand::set_fileSize(std::ifstream &file) {
    file.seekg(0, std::ios::end);
    fileSize = (long long) file.tellg();
    file.seekg(filePosition, std::ios::beg);
}

void UploadCommand::send_fileSize() {
    long long fileSizeToUpload = fileSize - filePosition;
    std::string fileSizeToUploadString = std::to_string(fileSizeToUpload);
    int sentBytes = send(Socket::get_createdSocket(),
                         fileSizeToUploadString.c_str(),
                         (int) fileSizeToUploadString.size(),
                         0);
    if (sentBytes == -1) {
        throw UploadCommandException("Error sending file size");
    }
}

void UploadCommand::send_file(std::ifstream &file) {
    char buffer[4];
    int totalSentBytes = 0;
    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        int readBytes = (int) file.gcount();
        int sentBytes = send(Socket::get_createdSocket(),
                             buffer,
                             readBytes,
                             0);
        if (sentBytes == -1) {
            file.close();
            throw ClientException("File uploading failed");
        }
        totalSentBytes += sentBytes;
        std::cout << " Sent   :" << totalSentBytes * 100 / fileSize << "%" << std::endl;
    }
}


