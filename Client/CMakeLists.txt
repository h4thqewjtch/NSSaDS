cmake_minimum_required(VERSION 3.27)
project(Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(Client main.cpp
        Exception/ClientException/ClientException.cpp
        Exception/ClientException/ClientException.h
        Socket/Socket.cpp
        Socket/Socket.h
        Command/Command.h
        UploadCommand/UploadCommand.cpp
        UploadCommand/UploadCommand.h
        DownloadCommand/DownloadCommand.cpp
        DownloadCommand/DownloadCommand.h
        Exception/DownloadCommandException/DownloadCommandException.cpp
        Exception/DownloadCommandException/DownloadCommandException.h
        Exception/SocketException/SocketException.cpp
        Exception/SocketException/SocketException.h
        Exception/UploadCommandException/UploadCommandException.cpp
        Exception/UploadCommandException/UploadCommandException.h)

target_link_libraries(Client ws2_32)