#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>
using namespace std;

queue<int> q;
int i = 0;
const int maxn = 200;

void* producer(void* args){
	while(true){
		if (i >= maxn){
			return nullptr;
		}	
		int val = i++;
		q.push(val);
		cout << "produce: " << val << endl;
		sleep(0.01);
	}
}

void* consumer(void* args){
	while(true){
		int val = q.front();
		q.pop();
		cout << "consume: " << val << endl;
		//sleep(0.1);
	}
}

int main(){
	pthread_t t1,t2;
	
	pthread_create(&t1, nullptr, producer, nullptr);
	pthread_create(&t2, nullptr, consumer, nullptr);

	pthread_join(t1, nullptr);
	pthread_join(t2, nullptr);

	return 0;	

}
