#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

int count=0;
const int sum = 1000;

void* cal(void* arg){
	while(true){
		if(count >= sum){
			return nullptr;
		}
		count++;
		cout<< "thread: "<< pthread_self()  << " count: "  << count << endl;
		sleep(0.1);
	}
}

int main(){
	pthread_t t1,t2,t3;
	
	pthread_create(&t1, nullptr, cal, nullptr);
	pthread_create(&t2, nullptr, cal, nullptr);
	pthread_create(&t3, nullptr, cal, nullptr);
	
	cout << "Main"  << getpid() << endl;	
	pthread_join(t1, nullptr);
//	cout << "t1 created" << endl;
	pthread_join(t2, nullptr);
//	cout << "t2 created" << endl;

	pthread_join(t3, nullptr);

//	cout << "t3 created" << endl;


	return 0;
	
}
