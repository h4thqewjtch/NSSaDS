#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <iostream>
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <cstdio>
#include <vector>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")

#include "../Exception/SocketException/SocketException.h"

class Socket {
private:
    static SOCKET createdSocket;

    static sockaddr_in serverAddress;

    static SOCKET connectedSocket;

    static WSAData wsaData;

    static std::string get_ipv4_server_address();

    static std::vector<std::string> get_ip_addresses_from_adapter_addresses(IP_ADAPTER_ADDRESSES_LH *);

    static std::vector<std::string> get_ip_addresses_from_unicast_addresses(IP_ADAPTER_UNICAST_ADDRESS *);

    static std::string get_ip_address_from_socket_address(sockaddr *);

    static void show_ipv4_server_address(std::string &);

    static int get_server_port();

    static void set_address_structure(std::string &, int);

public:
    Socket() = default;

    static SOCKET get_connectedSocket();

    static void wsaStartup();

    static void create_socket();

    static void set_server_address();

    static void bind_socket_to_address();

    static void listen_link_chanel();

    static void accept_connection();

    static void set_socket_timeout(int);

    static void clear_socket_buffer();

    static void close(const std::string &);

};

#endif //SERVER_SOCKET_H
