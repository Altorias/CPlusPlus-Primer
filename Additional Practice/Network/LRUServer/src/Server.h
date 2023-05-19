//
// Created by Charliegu on 2023/5/15.
//

#ifndef LRUSERVER_SERVER_H
#define LRUSERVER_SERVER_H


#include <string>
#include <mutex>
#include <jsoncpp/json/json.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include "ServerResourceQueue.h"
#include "Logger.h"
#include "CacheManager.h"
#include "RequestHandler.h"
#include "Network.h"



class Server {
private:
    // std::string conf_file_;
    int server_socket_;
    ServerResourceQueue* server_resource_queue_;
    int seq_;
    Logger* port_logger_;
    Logger* opr_logger_;
    CacheManager* cache_manager_;
    int port_;
    std::string address_;
    int server_resource_queue_capacity_;
    int cache_capacity_;
    int consumer_threads_;
    int buffer_size_;
    std::string port_logger_file_path_;
    std::string opr_logger_file_path_;

public:
    Server();

    bool Init(const std::string& conf_file);
    bool StartServer();
    void Run();
    void Quit() const;


};


#endif //LRUSERVER_SERVER_H





