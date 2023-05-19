//
// Created by Charliegu on 2023/5/15.
//


#ifndef LRUSERVER_REQUEST_HANDLER_H
#define LRUSERVER_REQUEST_HANDLER_H


#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include "CacheManager.h"
#include "Logger.h"
#include "jsoncpp/json/json.h"
#include "ServerResourceQueue.h"


class RequestHandler {
private:
    static const int OK = 200;
    static const int NOT_FOUND = 404;
    static const int INTERNAL_SERVER_ERROR = 500;
    static const int QUIT = -1;
    Json::Reader json_reader_;

//    std::string handleGetRequest(const Json::Value& root);
//    std::string handleWriteRequest(const Json::Value& root);
    int HandleRequest(const std::string& json, std::string& result,Logger* logger, CacheManager* cache_manager,const int seq);

    void SendResponse(int client_id,int code,const std::string& res_message);

public:
    RequestHandler();
    void HandleResourceQueue(ServerResourceQueue* server_resource_queue, Logger* logger, CacheManager* cache_manager);


//    RequestHandler(CacheManager& cacheManager, Logger& logger);
//    std::string handleRequest(const std::string& request);


};



#endif //LRUSERVER_REQUESTHANDLER_H
