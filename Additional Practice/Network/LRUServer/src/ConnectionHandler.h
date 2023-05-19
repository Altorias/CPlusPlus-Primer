//
// Created by Charliegu on 2023/5/17.
//

#ifndef LRUSERVER_CONNECTIONHANDLER_H
#define LRUSERVER_CONNECTIONHANDLER_H

#include "ServerResourceQueue.h"
#include "Logger.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <thread>
#include <chrono>
#include <sys/select.h>


class ConnectionHandler {
private:
    char* buffer_; // buffer数组
    int buffer_size_;

public:
    ConnectionHandler();
    ~ConnectionHandler();

    void Init(int buffer_size);

    void HandleConnections(ServerResourceQueue* server_resource_queue, const int seq, const int client_socket, Logger* port_logger);
};


#endif //LRUSERVER_CONNECTIONHANDLER_H
