#ifndef TS_QUEUE_H
#define TS_QUEUE_H

#include <pthread.h>
#include <semaphore.h>
#include <queue>

template <typename T>
class ThreadSafeQueue{
private:
	int max_capacity;
	std::queue<T> ts_queue;
	sem_t m_empty;
	sem_t m_full;
	pthread_mutex_t lock;

public:
	// 构造函数
	ThreadSafeQueue(){
		sem_init(&m_empty, 0, 0);
		// 设计为队列最大容量
		sem_init(&m_full,0,0);
		pthread_mutex_init(&lock, nullptr);
		
	};
	// 析构函数
	~ThreadSafeQueue(){
		sem_destroy(&m_empty);
		sem_destroy(&m_full);
		pthread_mutex_destroy(&lock);
	};

	void Init(int max_num){
		max_capacity = max_num;
		sem_init(&m_full,0,max_capacity);
	}
	
	void WaitTillPush(T& num){
		sem_wait(&m_full);
		pthread_mutex_lock(&lock);
		ts_queue.push(num);
		pthread_mutex_unlock(&lock);
		sem_post(&m_empty);		
	}

	void WaitTillPop(T& num){
		sem_wait(&m_empty);
		pthread_mutex_lock(&lock);
		num = ts_queue.front();
		ts_queue.pop();	
		pthread_mutex_unlock(&lock);
		sem_post(&m_full);
		
	}
};


#endif






