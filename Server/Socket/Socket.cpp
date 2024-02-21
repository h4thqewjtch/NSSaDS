#include "Socket.h"

SOCKET Socket::createdSocket = INVALID_SOCKET;

SOCKET Socket::connectedSocket = INVALID_SOCKET;

sockaddr_in Socket::serverAddress = {0};

WSAData Socket::wsaData;

SOCKET Socket::get_connectedSocket() {
    return connectedSocket;
}

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
    std::string ipv4Address = get_ipv4_server_address();
    show_ipv4_server_address(ipv4Address);
    int serverPort = get_server_port();
    set_address_structure(ipv4Address, serverPort);
}

std::string Socket::get_ipv4_server_address() {
    ULONG bufferLength = 0;
    if (GetAdaptersAddresses(AF_INET,
                             GAA_FLAG_INCLUDE_PREFIX,
                             nullptr,
                             nullptr,
                             &bufferLength) != ERROR_BUFFER_OVERFLOW) {
        throw SocketException("Error getting adapters addresses");
    }
    std::vector<char> buffer(bufferLength);
    auto adapterAddresses = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(&buffer[0]);
    if (GetAdaptersAddresses(AF_INET,
                             GAA_FLAG_INCLUDE_PREFIX,
                             nullptr,
                             adapterAddresses,
                             &bufferLength) != NO_ERROR) {
        throw SocketException("Error getting adapters information");
    }
    std::vector<std::string> ipAddresses = get_ip_addresses_from_adapter_addresses(adapterAddresses);
    std::string ipv4Address = ipAddresses[ipAddresses.size() - 2];
    return ipv4Address;
}

std::vector<std::string> Socket::get_ip_addresses_from_adapter_addresses(IP_ADAPTER_ADDRESSES_LH *adapterAddresses) {
    std::vector<std::string> ipAddressesVector = {};
    while (adapterAddresses) {
        IP_ADAPTER_UNICAST_ADDRESS *unicastAddress = adapterAddresses->FirstUnicastAddress;
        std::vector<std::string> subVector = get_ip_addresses_from_unicast_addresses(unicastAddress);
        ipAddressesVector.insert(ipAddressesVector.end(),
                                 subVector.begin(),
                                 subVector.end());
        adapterAddresses = adapterAddresses->Next;
    }
    return ipAddressesVector;
}

std::vector<std::string> Socket::get_ip_addresses_from_unicast_addresses(IP_ADAPTER_UNICAST_ADDRESS *unicastAddress) {
    std::vector<std::string> ipAddressesVector = {};
    while (unicastAddress) {
        sockaddr *socketAddress = unicastAddress->Address.lpSockaddr;
        ipAddressesVector.push_back(get_ip_address_from_socket_address(socketAddress));
        unicastAddress = unicastAddress->Next;
    }
    return ipAddressesVector;
}

std::string Socket::get_ip_address_from_socket_address(sockaddr *socketAddress) {
    std::string ipAddress;
    if (socketAddress->sa_family == AF_INET) {
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET,
                  &reinterpret_cast<sockaddr_in *>(socketAddress)->sin_addr,
                  ip,
                  INET_ADDRSTRLEN);
        ipAddress = std::string(ip);
    }
    return ipAddress;
}

void Socket::show_ipv4_server_address(std::string &ipv4Address) {
    std::cout << "Server IPv4 address   :" << ipv4Address << "\n";
}

int Socket::get_server_port() {
    std::cout << "Enter server port     :";
    int port;
    std::cin >> port;
    return port;
}

void Socket::set_address_structure(std::string &ipv4Address, int serverPort) {
    serverAddress = sockaddr_in();
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(ipv4Address.c_str());
    serverAddress.sin_port = htons(serverPort); // Port, where server will listen
}

void Socket::bind_socket_to_address() {
    if (bind(createdSocket,
             reinterpret_cast<SOCKADDR *>(&serverAddress),
             sizeof(serverAddress)) == SOCKET_ERROR) {
        throw SocketException("Error binding socket to address");
    }
}

void Socket::listen_link_chanel() {
    if (listen(createdSocket, SOMAXCONN) == SOCKET_ERROR) {
        throw SocketException("Error setting queue waiting connections");
    }
    std::cout << "Server is running. Waiting connections...\n";
}

void Socket::accept_connection() {
    connectedSocket = accept(createdSocket,
                             nullptr,
                             nullptr);
    if (connectedSocket == INVALID_SOCKET) {
        throw SocketException("Error setting connections with client");
    }
    std::cout << "Connection accepted\n";
}

void Socket::set_socket_timeout(int timeout){
    setsockopt(createdSocket,
               SOL_SOCKET,
               SO_RCVTIMEO,
               (const char *) &timeout,
               sizeof(timeout));
}

void Socket::clear_socket_buffer(){
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

void Socket::close(const std::string &sockets) {
    if (sockets.find("client") != std::string::npos) {
        closesocket(connectedSocket);
        std::cout << "Session is closed\n";
    }
    if (sockets.find("server") != std::string::npos) {
        closesocket(createdSocket);
        WSACleanup();
        std::cout << "Server is disabled\n";
    }
}
