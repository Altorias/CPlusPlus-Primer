//
// Created by Charliegu on 2023/5/18.
//

#include "Client.h"


Client::Client(const std::string &ip_address, int port)
        : ip_address_(ip_address), port_(port), buffer_size_(1024), client_socket_(0) {}

void Client::ConnectToServer() {
    // 创建套接字
    client_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_ == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }

    // 设置服务器地址和端口
    // 指定协议族，设置IP地址和端口号
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip_address_.c_str(), &server_address.sin_addr);
    server_address.sin_port = htons(port_);

    // 连接到服务器
    if (connect(client_socket_, reinterpret_cast<sockaddr *>(&server_address), sizeof(server_address)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        close(client_socket_);
        return;
    }

    std::cout << "Connected to server " << ip_address_ << std::endl;

    // 处理连接
    HandleConnection();

    // 关闭套接字
    close(client_socket_);
}

void Client::HandleConnection() {
    Json::Reader reader;
    while (true) {
        int opr = 0;
        std::string method;
        std::string key;
        std::string value;

        std::cout << "请输入操作类别: " << std::endl;
        std::cout << "1 - Get" << std::endl;
        std::cout << "2 - Write" << std::endl;
        std::cout << "-1 - Quit" << std::endl;
        std::cin >> opr;
        std::cin.ignore();

        if (opr == -1) {
            method = "quit";
        } else if (opr == 1) {
            method = "get";
            std::cout << "请输入key: " << std::endl;
            getline(std::cin, key);
            if (key.empty()) {
                std::cout << "key不能为空" << std::endl;
                continue;
            }
        } else if (opr == 2) {
            method = "write";
            std::cout << "请输入key: " << std::endl;
            getline(std::cin, key);
            if (key.empty()) {
                std::cout << "key不能为空" << std::endl;
                continue;
            }
            std::cout << "请输入value: " << std::endl;
            getline(std::cin, value);
            if (value.empty()) {
                std::cout << "value不能为空" << std::endl;
                continue;
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入有误，请重新输入" << std::endl;
            continue;
        }

        Json::StreamWriterBuilder writer;
        Json::Value root;
        root["method"] = method;
        root["key"] = key;
        root["value"] = value;
        writer["indentation"] = "";
        std::string json_string = Json::writeString(writer, root);
        // 打印请求信息
        std::cout << "向服务器发送信息: " << json_string << std::endl;

        // 发送请求到服务器
        if (send(client_socket_, json_string.c_str(), json_string.length(), 0) == -1) {
            std::cerr << "发送信息失败" << std::endl;
            break;
        }

        // 接收服务器返回的数据
        char buffer[buffer_size_];
        memset(buffer, 0, sizeof(buffer));

        if (recv(client_socket_, buffer, buffer_size_, 0) == 0) {
            std::cout << "已断开连接" << std::endl;
            return;
        }

        // 打印接收到的信息
        std::cout << "从服务器接收信息: " << buffer << std::endl;

        // 反序列化字符串
        std::string response = std::string(buffer);

        // 解析返回的Json字符串
        Json::Value jsonResponse;
        reader.parse(response, jsonResponse);
        int code = jsonResponse["code"].asInt();
        std::string message = jsonResponse["message"].asString();

        // 打印转义后的字符串
        std::cout << "code: " << code << std::endl;
        std::cout << "message: " << message << std::endl;

        if (opr == OPERATION_QUIT) {
            break;
        }
    }
    close(client_socket_);
}


