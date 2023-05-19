#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include "Client.h"
using namespace std;

int main(int argc, char* argv[]){
    string address = "0.0.0.0";
    int port = 8050;
    Client* client = new Client(address,port);
    client->ConnectToServer();

    return 0;

}
