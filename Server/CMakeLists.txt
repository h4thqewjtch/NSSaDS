cmake_minimum_required(VERSION 3.27)
project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server main.cpp
        Exception/ServerException/ServerException.cpp
        Exception/ServerException/ServerException.h
        Socket/Socket.cpp
        Socket/Socket.h
        Command/Command.h
        EchoCommand/EchoCommand.cpp
        EchoCommand/EchoCommand.h
        CloseCommand/CloseCommand.cpp
        CloseCommand/CloseCommand.h
        TimeCommand/TimeCommand.cpp
        TimeCommand/TimeCommand.h
        DownloadCommand/DownloadCommand.cpp
        DownloadCommand/DownloadCommand.h
        UploadCommand/UploadCommand.cpp
        UploadCommand/UploadCommand.h
        Exception/SocketException/SocketException.cpp
        Exception/SocketException/SocketException.h
        Exception/DownloadCommandException/DownloadCommandException.cpp
        Exception/DownloadCommandException/DownloadCommandException.h
        Exception/UploadCommandException/UploadCommandException.cpp
        Exception/UploadCommandException/UploadCommandException.h
)

target_link_libraries(Server ws2_32)
target_link_libraries(Server IPHLPAPI)