//
// Created by Charliegu on 2023/5/15.
//

#ifndef LRUSERVER_NETWORK_H
#define LRUSERVER_NETWORK_H


#include <string>
#include <thread>
#include <functional>
#include <memory>
#include <unordered_map>
#include "RequestHandler.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ServerResourceQueue.h"
#include "Logger.h"
#include "ConnectionHandler.h"

class Network {
private:
    int server_socket_; // 服务器套接字
    int seq_; // 操作流水号，默认为0
    int buffer_size_; // buffer大小，从配置文件中读取

public:
    Network();
    ~Network();

    void Init(int server_socket, int seq, int buffer_size);
    void AcceptConnections(ServerResourceQueue* cache_operation_queue, Logger* port_logger);
};




#endif //LRUSERVER_NETWORK_H
