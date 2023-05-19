//
// Created by Charliegu on 2023/5/15.
//

#include "RequestHandler.h"

RequestHandler::RequestHandler() {}

void RequestHandler::HandleResourceQueue(ServerResourceQueue *server_resource_queue, Logger *logger,
                                         CacheManager *cache_manager) {
    while (true) {
        // 从资源队列中拿出数据
        try {
            ResourceUnit resourceUnit;
            server_resource_queue->WaitTillPop(resourceUnit);
            std::cout << std::this_thread::get_id()
                      << " 从资源队列中获取" << std::endl;
            int seq = resourceUnit.seq;
            int client_socket_id = resourceUnit.client_socket_id;
            std::string json = resourceUnit.json;
            logger->WriteLogDebug(LOCATION(), "从队列中取出数据[" + json + "][seq=" + std::to_string(seq) + "]");
            std::string result;
            int code;
            code = HandleRequest(json, result, logger, cache_manager, seq);
            SendResponse(client_socket_id, code, result);
            if (code == QUIT){
                break;
            }
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            return;
        }
    }
    return;
}

int RequestHandler::HandleRequest(const std::string &json, std::string &result, Logger *logger,
                                  CacheManager *cache_manager, const int seq) {
    // 检查参数
    if (json.empty()) {
        logger->WriteLogWarning(LOCATION(), "客户端传输的数据为空 [seq=" + std::to_string(seq) + "]");
        result = "客户端数据为空";
        return NOT_FOUND;
    }

    Json::Value root;
    std::string method;
    std::string key;
    std::string value;

    //Json字符串反序列化
    if (json_reader_.parse(json, root)) {
        method = root["method"].asString();
        key = root["key"].asString();
        value = root["value"].asString();
    } else {
        logger->WriteLogError(LOCATION(),
                              "客户端传输的数据[" + json + "]反序列化失败 [seq=" + std::to_string(seq) + "]");
        result = "Json字符串反序列化失败";
        return INTERNAL_SERVER_ERROR;
    }

    //检查method和key，无论何时method和key都不能为空
    if (method.empty()) {
        logger->WriteLogWarning(LOCATION(),
                                "客户端传输的数据[" + json + "]中的method字段为空 [seq=" + std::to_string(seq) + "]");
        result = "传递的method不存在";
        return NOT_FOUND;
    }

    if (method == "quit") {
        logger->WriteLogDebug(LOCATION(),
                              "从客户端收到quit指令，与客户端断开连接 [seq=" + std::to_string(seq) + "]");
        result = "您已与服务器断开连接";
        return QUIT;
    }

    if (key.empty()) {
        logger->WriteLogWarning(LOCATION(),
                                "客户端传输的数据[" + json + "]中的key字段为空 [seq=" + std::to_string(seq) + "]");
        result = "传递的key为空";
        return NOT_FOUND;
    }


    if (method == "get") {
        std::string get_result;
        if (cache_manager->Get(key, get_result, logger, seq)) {
            if (get_result.empty()) {
                logger->WriteLogDebug(LOCATION(),
                                      "客户端从缓存中查询key=[" + key + "]的值，没有搜索到相应的记录 [seq=" +
                                      std::to_string(seq) + "]");
                result = "查询key=[" + key + "]的值成功，但是没有搜索到相应的记录";
                return OK;
            } else {
                logger->WriteLogDebug(LOCATION(),
                                      "客户端从缓存中查询key=[" + key + "]的值，其value=[" + get_result + "][seq=" +
                                      std::to_string(seq) + "]");
                result = "查询key=[" + key + "]的值成功，其value=[" + get_result + "]";
                return OK;
            }
        } else {
            logger->WriteLogError(LOCATION(),
                                  "客户端从缓存中查询key=[" + key + "]的值操作失败 [seq=" +
                                  std::to_string(seq) + "]");
            result = "查询key=[" + key + "]的值失败，服务器内部错误";
            return INTERNAL_SERVER_ERROR;
        }
    }

    if (method == "write") {
        // 首先检查参数value
        if (value.empty()) {
            logger->WriteLogWarning(LOCATION(),
                                    "客户端传输的数据[" + json + "]中的value字段为空 [seq=" + std::to_string(seq) +
                                    "]");
            result = "传递的value为空";
            return NOT_FOUND;
        }
        if (cache_manager->Write(key, value, logger, seq)) {
            logger->WriteLogDebug(LOCATION(),
                                  "客户端从缓存写入key=[" + key + "],value=[" + value + "]的值，操作成功 [seq=" +
                                  std::to_string(seq) + "]");
            result = "往缓存中写入key=[" + key + "],value=[" + value + "]的值成功";
            return OK;
        } else {
            logger->WriteLogError(LOCATION(),
                                  "客户端从缓存写入key=[" + key + "],value=[" + value + "]的值，操作失败 [seq=" +
                                  std::to_string(seq) + "]");
            result = "往缓存中写入key=[" + key + "],value=[" + value + "]的值失败，服务器内部错误";
            return INTERNAL_SERVER_ERROR;
        }
    } else {
        logger->WriteLogError(LOCATION(),
                              "客户端传输的数据[" + json + "]中的method字段不合法 [seq=" + std::to_string(seq) + "]");
        result = "传递的method不正确";
        return NOT_FOUND;
    }
    return 0;
}

void RequestHandler::SendResponse(int client_id, int code, const std::string &res_message) {
    Json::Value root;
    root["code"] = Json::Value(code);
    root["message"] = Json::Value(res_message);
    Json::StreamWriterBuilder writer;
    writer["indentation"] = "";
    std::string json_string = Json::writeString(writer, root);
    ssize_t sentBytes = send(client_id, json_string.c_str(), json_string.length(), 0);
    if (sentBytes < 0) {
        std::cerr << "Failed to send data." << std::endl;
        return;
    }
    if (QUIT == code) {
        std::cout << "与客户端" + std::to_string(client_id) + "断开连接" << std::endl;
        close(client_id);
    }
}
