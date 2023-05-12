#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

int count = 0;
const int sum = 1000;
pthread_mutex_t mutex;

void* cal(void* args){
	while(true){
		pthread_mutex_lock(&mutex);

		if(count >= sum){
			pthread_mutex_unlock(&mutex);
			return nullptr;
		}

		int val = count;
		count++;

		cout<< "thread: "<<pthread_self()  <<" val: " << val <<endl;
		pthread_mutex_unlock(&mutex);
		sleep(0.1);
	}
}

int main(){
	pthread_t t1,t2,t3;
	
	pthread_create(&t1, nullptr, cal, nullptr);
	pthread_create(&t2, nullptr, cal, nullptr);
	pthread_create(&t3, nullptr, cal, nullptr);

	pthread_join(t1, nullptr);
	pthread_join(t2, nullptr);
	pthread_join(t3, nullptr);

	return 0;


}
