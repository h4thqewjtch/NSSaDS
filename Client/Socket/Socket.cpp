#include "Socket.h"

SOCKET Socket::createdSocket = INVALID_SOCKET;

sockaddr_in Socket::serverAddress = {0};

WSADATA Socket::wsaData;

void Socket::wsaStartup() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw SocketException("Invalid initialization WinSock");
    }
}

void Socket::create_socket() {
    createdSocket = socket(AF_INET,
                           SOCK_STREAM,
                           IPPROTO_TCP);
    if (createdSocket == INVALID_SOCKET) {
        throw SocketException("Error creating socket");
    }
}

void Socket::set_server_address() {
    std::string serverIPv4Address = get_server_ipv4_address();
    const char *serverIPv4Address_const_char = serverIPv4Address.c_str();
    int serverPort = get_server_port();
    set_address_structure(serverIPv4Address_const_char, serverPort);
}

std::string Socket::get_server_ipv4_address() {
    std::cout << "Enter server IPv4 address   :";
    std::string ipv4Address;
    std::cin >> ipv4Address;
    return ipv4Address;
}

int Socket::get_server_port() {
    std::cout << "Enter server port           :";
    int port;
    std::cin >> port;
    return port;
}

SOCKET Socket::get_createdSocket() {
    return createdSocket;
}

void Socket::set_address_structure(const char *serverIPv4Address, int &serverPort) {
    serverAddress = sockaddr_in();
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIPv4Address); // Server IP-address
    serverAddress.sin_port = htons(serverPort); // Port, where server listen
}

void Socket::connect_to_server() {
    if (connect(createdSocket,
                reinterpret_cast<SOCKADDR *>(&serverAddress),
                sizeof(serverAddress)) == SOCKET_ERROR) {
        throw SocketException("Error connecting to server");
    }
    std::cout << "Client connected to server\n";
}

void Socket::set_socket_timeout(int timeout){
    setsockopt(createdSocket,
               SOL_SOCKET,
               SO_RCVTIMEO,
               (const char *) &timeout,
               sizeof(timeout));
}

void Socket::clear_socket_buffer() {
    char buffer[1024];
    int bytesRead;
    do {
        bytesRead = recv(createdSocket,
                         buffer,
                         sizeof(buffer),
                         0);
        if (bytesRead == SOCKET_ERROR) {
            break;
        }
    } while (bytesRead > 0);
}

void Socket::close_socket() {
    closesocket(createdSocket);
    WSACleanup();
    std::cout << "Session is closed" << std::endl;
}
