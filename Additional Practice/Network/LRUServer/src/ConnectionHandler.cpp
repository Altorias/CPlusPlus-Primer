//
// Created by Charliegu on 2023/5/17.
//

#include "ConnectionHandler.h"


ConnectionHandler::ConnectionHandler() : buffer_(nullptr), buffer_size_(0) {}

ConnectionHandler::~ConnectionHandler() {
    delete[] buffer_;
}

void ConnectionHandler::Init(int buffer_size) {
    buffer_size_ = buffer_size;
    buffer_ = new char[buffer_size];
}

void
ConnectionHandler::HandleConnections(ServerResourceQueue *server_resource_queue, const int seq, const int client_socket,
                                     Logger *port_logger) {

    int max_fd = client_socket + 1;
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(client_socket, &read_fds);

    timeval timeout{};
    timeout.tv_sec = 60;  // 超时时间为1分钟
    timeout.tv_usec = 0;

    while (true) {
        int result = select(max_fd, &read_fds, nullptr, nullptr, &timeout);
        if (result == -1) {
            // 处理 select 错误
            break;
        } else if (result == 0) {
            // 超时，断开连接
            std::cout << "客户端" + std::to_string(client_socket) + "太长时间未发送消息,断开连接"<< std::endl;
            break;
        } else {
            // 检查套接字是否准备好读取数据
            if (FD_ISSET(client_socket, &read_fds)) {
                int bytes_received = recv(client_socket, buffer_, buffer_size_ - 1, 0);
                if (bytes_received == 0) {
                    break;
                } else if (bytes_received < 0) {
                    port_logger->WriteLogError(
                            LOCATION(),
                            "从客户端[" + std::to_string(client_socket) + "]获取信息失败 [seq=" +
                            std::to_string(seq) + "]");
                    break;
                } else {
                    // 记录请求
                    port_logger->WriteLogDebug(
                            LOCATION(),
                            "[socket_id:" + std::to_string(client_socket) + "][json:" + buffer_ + "] [seq=" +
                            std::to_string(seq) +
                            "]");

                    // 构建资源单位
                    ResourceUnit resourceUnit;
                    resourceUnit.seq = seq;
                    resourceUnit.client_socket_id = client_socket;
                    resourceUnit.json = std::string(buffer_);

                    // 将数据加入队列
                    std::cout << std::this_thread::get_id()
                              << " 响应客户端[" + std::to_string(client_socket) + "]往资源队列中添加" << std::endl;
                    server_resource_queue->WaitTillPush(resourceUnit);

                    // 更新超时时间
                    timeout.tv_sec = 60;
                    timeout.tv_usec = 0;
                }
            }
        }
    }

    close(client_socket);
}
