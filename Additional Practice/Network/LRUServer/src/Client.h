//
// Created by Charliegu on 2023/5/15.
//

#ifndef LRUSERVER_CLIENT_H
#define LRUSERVER_CLIENT_H

#include <string>
#include <jsoncpp/json/json.h>

class Client {
public:
    Client(const std::string& ip_address, int port);

    // Connect to server
    bool connectToServer();

    // Send request and receive response
    bool sendRequest(const std::string& key, std::string& value);

private:
    std::string m_ip_address;
    int m_port;
    int m_socket_fd;

    // Build JSON request
    Json::Value buildRequest(const std::string& key);

    // Parse JSON response
    bool parseResponse(const std::string& response, std::string& value);
};

#endif // CLIENT_H


#endif //LRUSERVER_CLIENT_H
