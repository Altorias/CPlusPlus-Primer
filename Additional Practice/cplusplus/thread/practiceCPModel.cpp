#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <queue>
using namespace std;

// 缓存区队列
queue<int> capacity;

// 缓存区容量
const int max_capacity = 20;

// 生产者和消费者数量
const int max_producer = 3;
const int max_consumer = 3;

// 互斥锁,调用头文件中的Init
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 条件变量，指示满与空
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void* producer(void* args){
	while(true){
		int num = rand() % 100;
		
		pthread_mutex_lock(&mutex);
		
		// 此处用while防止假唤醒
		while(capacity.size() == max_capacity){
			pthread_cond_wait(&not_full, &mutex);
		}

		capacity.push(num);

		cout << "Producer: " << pthread_self() << " item: " << num << endl;
		
		// 记得唤醒其他线程
		pthread_cond_signal(&not_empty);

		pthread_mutex_unlock(&mutex);

		sleep(0.01);	
	}
}

void* consumer(void* args){
	while(true){
		pthread_mutex_lock(&mutex);

		while(capacity.empty()){
			pthread_cond_wait(&not_empty, &mutex);
		}

		int num = capacity.front();
		capacity.pop();

		cout << "Comsumer: " << pthread_self() << " item: " << num << endl;

		pthread_cond_signal(&not_full);

		pthread_mutex_unlock(&mutex);

		sleep(0.01);
	}
}

int main(){
	// 初始化random seed;
	srand(0);
	// 初始化生产者和消费者
	pthread_t producer_threads[max_producer];
	pthread_t consumer_threads[max_consumer];

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


	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&not_full);
	pthread_cond_destroy(&not_empty);
	
	return 0;
		
}
