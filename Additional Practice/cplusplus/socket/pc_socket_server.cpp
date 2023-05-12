#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include "ts_queue.h"
using namespace std;

struct Message{
	int client_socket;
	char buffer[1024];
};

const int server_port = 8050;
ThreadSafeQueue<Message> message_queue;

void* handle_message(void* arg) {
	while(true){
		Message message;
		message_queue.WaitTillPop(message);
		string res_message = message.buffer;
		if (res_message == "quit"){
			cout << "Closing client " << message.client_socket << endl;
			close(message.client_socket);
		}else{
			cout << "Sending client " << message.client_socket << " : " << res_message << endl;
//			if(write(message.client_socket, res_message.c_str(), res_message.size() < 0)){	
//				cerr << "Failed Sending client " << message.client_socket << endl;
//			}
			write(message.client_socket, message.buffer, strlen(message.buffer));
		}
	}
}

void* handle_client(void* arg){
	int client_socket = *(int*)arg;

	char buffer[1024] = {0};
	while(true){
		int read_result = read(client_socket, buffer, 1024);
		if (read_result < 0){
			cerr << "Failed to read from socket: " << client_socket  << endl;
			break;
		} else if (read_result == 0){	
			cout << "Disconnected from socket: " << client_socket  << endl;
			break;
		}
		cout << "Received from " << client_socket << " : " << buffer  << endl;
		Message message = {client_socket, ""};
		strncpy(message.buffer, buffer, 1024);
		message_queue.WaitTillPush(message);
	}
	close(client_socket);
	cout << pthread_self() << " Connection closed" << endl;
	return nullptr;
}



int main(int argc, char* argv[]){
    message_queue.Init(20);
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	char ip[128] = {0};
	socklen_t client_length;
	if (server_socket == -1){
		cerr << "Failed to create socket " << endl;
		return -1;
	}

	// 初始化socket信息
	struct sockaddr_in client_address,server_address;
	server_address.sin_family = AF_INET;
	
    // 如果输入IP和端口
	if ( argc == 3){
		inet_pton(AF_INET, argv[1], &server_address.sin_addr);
		server_address.sin_port = htons(atoi(argv[2]));
	}else{
		server_address.sin_addr.s_addr = htonl(INADDR_ANY);
		server_address.sin_port = htons(server_port);
	}

	if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
		cerr << "Failed to bind to address " << endl;
		return -1;
	}

	if (listen(server_socket, 4) < 0){
		cerr << "Failed to listen to socket " << endl;
		return -1;
	}

	cout << "Server start at:" << inet_ntop(AF_INET,&server_address.sin_addr,ip,128) << ":" <<ntohs(server_address.sin_port) <<endl;
	cout << "Waiting for connection " << endl;

	// 此时加入消费者线程，返回数据
	pthread_t consumer_thread;
	if (pthread_create(&consumer_thread, nullptr,handle_message, nullptr ) < 0){
		cerr << "Failed to create consumer thread" << endl;
		return -1;
	}
	
	while(true){
		client_length = sizeof(client_address);
		int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_length);
		if ( client_socket < 0){
			cerr << "Failed to accept connection. " << endl;
			return -1;
		}
		cout << "Connection established " << endl;

		pthread_t thread_id;
		if (pthread_create(&thread_id, nullptr, handle_client, (void*)&client_socket)<0){
			cerr << "Failed to create client thread" <<endl;
			return -1;
		}
		pthread_detach(thread_id);
	}

	close(server_socket);
	return 0;
}

