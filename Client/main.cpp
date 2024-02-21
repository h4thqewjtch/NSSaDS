#include "DownloadCommand/DownloadCommand.h"
#include "UploadCommand/UploadCommand.h"
#include "Exception/ClientException/ClientException.h"
#include "Exception/SocketException/SocketException.h"
#include "Exception/DownloadCommandException/DownloadCommandException.h"
#include "Exception/UploadCommandException/UploadCommandException.h"

void work_with_server();

std::string get_request();

void send_request(std::string &);

void parse_request(std::string &);

std::string receive_response();

void show_response(std::string &);

int main() {
    try {
        Socket::wsaStartup();
        Socket::create_socket();
        Socket::set_server_address();
        Socket::connect_to_server();
        work_with_server();
    } catch (SocketException &socketException) {
        socketException.print_exceptionInfo();
    } catch (...) {
        ClientException clientException;
        clientException.print_exceptionInfo();
    }
    Socket::close_socket();
    return 0;
}

void work_with_server() {
    rewind(stdin);
    std::string request;
    do {
        try {
            request = get_request();
            send_request(request);
            parse_request(request);
            std::string response = receive_response();
            show_response(response);
        } catch (UploadCommandException &uploadCommandException) {
            uploadCommandException.print_exceptionInfo();
        } catch (DownloadCommandException &downloadCommandException) {
            downloadCommandException.print_exceptionInfo();
        } catch (ClientException &serverException) {
            serverException.print_exceptionInfo();
            request = "close";
        }
    } while (request != "close");
}

std::string get_request() {
    std::cout << ">";
    std::string request = "hello";
    getline(std::cin, request);
    return request;
}

void send_request(std::string &requestString) {
    const char *request = requestString.c_str();
    send(Socket::get_createdSocket(),
         request,
         (int) strlen(request),
         0);
}

void parse_request(std::string &request) {
    if (request.find("upload") != std::string::npos) {
        UploadCommand uploadCommand = UploadCommand();
        Command *command = &uploadCommand;
        command->run_command(request);
    } else if (request.find("download") != std::string::npos) {
        DownloadCommand downloadCommand = DownloadCommand();
        Command *command = &downloadCommand;
        command->run_command(request);
    }
}

std::string receive_response() {
    Socket::set_socket_timeout(0);
    char buffer[1024] = {0};
    int bytesRead = recv(Socket::get_createdSocket(),
                         buffer,
                         sizeof(buffer),
                         0);
    if (bytesRead == SOCKET_ERROR) {
        Socket::close_socket();
        throw ClientException("Error reading server data");
    }
    std::string response = std::string(buffer);
    return response.substr(0, bytesRead);
}

void show_response(std::string &response) {
    std::cout << " " << response << std::endl;
}
