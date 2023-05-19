//
// Created by Charliegu on 2023/5/18.
//

#ifndef LRUCLIENT_CLIENT_H
#define LRUCLIENT_CLIENT_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <limits>

class Client {
public:
    Client(const std::string& ipAddress, int port);
    void ConnectToServer();

private:
    void HandleConnection();
    std::string ParseResponse(const std::string& response);

    int port_;           // 端口号
    std::string ip_address_;  // IP地址
    int buffer_size_;     // buffer大小
    int client_socket_;
    static const int OPERATION_GET = 1;     // 特殊静态变量(用户操作类别)
    static const int OPERATION_WRITE = 2;
    static const int OPERATION_QUIT = -1;
};


#endif //LRUCLIENT_CLIENT_H
