#include "CloseCommand/CloseCommand.h"
#include "Command/Command.h"
#include "DownloadCommand/DownloadCommand.h"
#include "EchoCommand/EchoCommand.h"
#include "TimeCommand/TimeCommand.h"
#include "UploadCommand/UploadCommand.h"
#include "Socket/Socket.h"
#include "Exception/ServerException/ServerException.h"
#include "Exception/SocketException/SocketException.h"
#include "Exception/DownloadCommandException/DownloadCommandException.h"
#include "Exception/UploadCommandException/UploadCommandException.h"

std::string request;
std::string response;

TimeCommand timeCommand;

void work_with_client();

void receive_request();

void show_request();

void parse_request();

void send_response();

int main() {
    try {
        timeCommand = TimeCommand(TimeCommand::what_time_is_it_now());
        Socket::wsaStartup();
        Socket::create_socket();
        Socket::set_server_address();
        Socket::bind_socket_to_address();
        Socket::listen_link_chanel();
        while (true) {
            Socket::accept_connection();
            work_with_client();
        }
    } catch (SocketException &socketException) {
        socketException.print_exceptionInfo();
    } catch (...) {
        ServerException serverException;
        serverException.print_exceptionInfo();
    }
    Socket::close("client and server");
    return 0;
}

void work_with_client() {
    do {
        try {

            receive_request();
            show_request();
            parse_request();
            send_response();
        } catch (UploadCommandException &uploadCommandException) {
            uploadCommandException.print_exceptionInfo();
        } catch (DownloadCommandException &downloadCommandException) {
            downloadCommandException.print_exceptionInfo();
        } catch (ServerException &serverException) {
            serverException.print_exceptionInfo();
            Socket::close("client");
            response = "Session is closed";
        }
    } while (response != "Session is closed");
}

void receive_request() {
    Socket::set_socket_timeout(0);
    char requestBuffer[1024] = {0};
    int bytesRead = recv(Socket::get_connectedSocket(),
                         requestBuffer,
                         sizeof(requestBuffer),
                         0);
    if (bytesRead == SOCKET_ERROR) {
        throw ServerException("Error reading client data");
    }
    request = std::string(requestBuffer).substr(0, bytesRead);
}

void show_request() {
    std::cout << request << std::endl;
}

void parse_request() {
    if (request.find("echo") != std::string::npos) {
        EchoCommand echoCommand = EchoCommand();
        Command *command = &echoCommand;
        response = command->run_command(request);
    } else if (request.find("time") != std::string::npos) {
        Command *command = &timeCommand;
        response = command->run_command(request);
    } else if (request.find("upload") != std::string::npos) {
        UploadCommand uploadCommand = UploadCommand();
        Command *command = &uploadCommand;
        response = command->run_command(request);
    } else if (request.find("download") != std::string::npos) {
        DownloadCommand downloadCommand = DownloadCommand();
        Command *command = &downloadCommand;
        response = command->run_command(request);
    } else if (request.find("close") != std::string::npos) {
        CloseCommand closeCommand = CloseCommand();
        Command *command = &closeCommand;
        response = command->run_command(request);
    } else {
        response = "Unknown command";
    }
}

void send_response() {
    send(Socket::get_connectedSocket(), response.c_str(), (int) response.size(), 0);
}