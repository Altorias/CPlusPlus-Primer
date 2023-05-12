#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]){
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (argc < 2){
		cerr << "Need to input IP address and port" << endl;
		return -1;
	}	

	if (sockfd == -1){
		cerr << "Failed to create socket" << endl;
		return -1;
	}

	// 初始化结构体
	struct sockaddr_in server_address;
	bzero(&server_address, sizeof(server_address));
	
	// 指定协议族，设置IP地址和端口号
	server_address.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &server_address.sin_addr);
	server_address.sin_port = htons(atoi(argv[2]));

	if(connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0 ){
		cerr << "Failed to connect to server " << endl;
		close(sockfd);
		return -1;
	}	
	
	char buffer[1024];
	while(true){
		 // 读取用户输入
        cout << "Input message (quit to exit): ";
        string message;
        getline(cin, message);
        // 发送数据到服务器
        if (send(sockfd, message.c_str(), message.size(), 0) == -1){	
            cerr << "Failed to send message." << endl;
            break;
        }
        if (message == "quit") {
            break;
        }

        // 接收服务器返回的数据
        int len = recv(sockfd, buffer, sizeof(buffer), 0);
        if (len == -1) {
            cerr << "Failed to receive message." << endl;
            break;
        } else if (len == 0) {
            cerr << "Server closed the connection." << endl;
            break;
        }

        // 显示服务器返回的数据
        buffer[len] = '\0';
        cout << "Received message: " << buffer << endl;
	}

	close(sockfd);
	
	return 0;
	
}
