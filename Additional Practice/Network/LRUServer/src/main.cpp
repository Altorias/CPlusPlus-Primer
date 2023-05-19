#include <iostream>
#include <string>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "ServerResourceQueue.h"
#include "Logger.h"
#include "CacheManager.h"
#include "Server.h"

using namespace std;

bool FileExists(const std::string& file_name) {
    std::ifstream file(file_name);
    return file.good();
}

int main() {

// 测试Server
    string flag_file = "../script/close_server";
    Server *server = new Server;
    server->Init("../src/conf/conf.json");
    server->Run();
    while (true) {
        if (FileExists(flag_file)) {
            server->Quit();
            delete server;
            return 0;
        }
    }




}
