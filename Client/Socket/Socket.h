#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#include "../Exception/SocketException/SocketException.h"

class Socket {
private:
    static SOCKET createdSocket;
    static sockaddr_in serverAddress;
    static WSADATA wsaData;

    static std::string get_server_ipv4_address();

    static int get_server_port();

    static void set_address_structure(const char *, int &);

public:
    Socket() = default;

    static SOCKET get_createdSocket();

    static void wsaStartup();

    static void create_socket();

    static void set_server_address();

    static void connect_to_server();

    static void set_socket_timeout(int);

    static void clear_socket_buffer();

    static void close_socket();
};


#endif //CLIENT_SOCKET_H
