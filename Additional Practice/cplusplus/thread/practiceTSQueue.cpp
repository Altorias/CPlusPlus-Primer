#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "ts_queue.h"
using namespace std;

// 缓存区队列
ThreadSafeQueue<int> ts_queue;

// 缓存区容量
const int max_capacity = 20;

// 生产者和消费者数量
const int max_producer = 3;
const int max_consumer = 3;

void* producer(void* args){
	while(true){
		int num = rand() % 100;

		ts_queue.WaitTillPush(num);

		cout << "Producer: " << pthread_self() << " item: " << num << endl;

		sleep(0.01);	
	}
}

void* consumer(void* args){
	while(true){
		
		int num = 0;

		ts_queue.WaitTillPop(num);

		cout << "Comsumer: " << pthread_self() << " item: " << num << endl;

		//sleep(0.01);
	}
}

int main(){
	// 初始化生产者和消费者
	pthread_t producer_threads[max_producer];
	pthread_t consumer_threads[max_consumer];

	ts_queue.Init(max_capacity);

	for(int i = 0; i < max_producer; i++){
		pthread_create(&producer_threads[i], nullptr, producer, nullptr);
	}

	for(int i = 0; i < max_consumer; i++){
		pthread_create(&consumer_threads[i], nullptr, consumer, nullptr);
	} 
	
    for(int i = 0; i < max_producer; i++){
        pthread_join(producer_threads[i], nullptr);
    }
	
	for(int i = 0; i < max_consumer; i++){
		pthread_join(consumer_threads[i], nullptr);
	}
	
	return 0;
		
}
