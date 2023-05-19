//
// Created by Charliegu on 2023/5/15.
//

#include "Client.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>

using namespace std;

Client::Client(const string& ip_address, int port)
        : m_ip_address(ip_address), m_port(port), m_socket_fd(-1) {}

bool Client::connectToServer() {
    // Create socket
    m_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket_fd < 0) {
        cerr << "Failed to create socket" << endl;
        return false;
    }

    // Set server address
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(m_port);
    if (inet_pton(AF_INET, m_ip_address.c_str(), &serv_addr.sin_addr) <= 0) {
        cerr << "Invalid address or address not supported" << endl;
        close(m_socket_fd);
        m_socket_fd = -1;
        return false;
    }

    // Connect to server
    if (connect(m_socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection failed" << endl;
        close(m_socket_fd);
        m_socket_fd = -1;
        return false;
    }

    return true;
}

Json::Value Client::buildRequest(const std::string& key) {
    Json::Value request;
    request["command"] = "get";
    request["key"] = key;
    return request;
}

bool Client::parseResponse(const string& response, string& value) {
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(response, root)) {
        cerr << "Failed to parse response: " << response << endl;
        return false;
    }

    if (root["status"].asString() != "success") {
        cerr << "Request failed: " << root["message"].asString() << endl;
        return false;
    }

    if (root.isMember("value")) {
        value = root["value"].asString();
    } else {
        cerr << "No value returned in response" << endl;
        return false;
    }

    return true;
}

bool Client::sendRequest(const string& key, string& value) {
    if (m_socket_fd < 0) {
        cerr << "Not connected to server" << endl;
        return false;
    }

    // Build request
    Json::
}