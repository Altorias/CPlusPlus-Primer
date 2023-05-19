//
// Created by Charliegu on 2023/5/15.
//
#include "Network.h"

Network::Network() : server_socket_(0), seq_(0), buffer_size_(0) {}

Network::~Network() {}

void Network::Init(int server_socket, int seq, int buffer_size) {
    server_socket_ = server_socket;
    seq_ = seq;
    buffer_size_ = buffer_size;
}

void Network::AcceptConnections(ServerResourceQueue *server_resource_queue, Logger *port_logger) {
    while (true) {
        struct sockaddr_in clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);

        int clientSocket = accept(server_socket_, (struct sockaddr *) &clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            std::cerr << "Failed to accept connection." << std::endl;
            continue;
        } else if (clientSocket > 0){
            seq_++;
            auto *handler = new ConnectionHandler();
            handler->Init(buffer_size_);
            std::cout << "与客户端" + std::to_string(clientSocket) + "建立连接" << std::endl;
            std::thread t(&ConnectionHandler::HandleConnections, handler, server_resource_queue, seq_, clientSocket,
                          port_logger);
            t.detach();
        }

    }
}
