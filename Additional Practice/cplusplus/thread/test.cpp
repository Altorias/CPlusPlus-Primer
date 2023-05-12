#include <iostream>
#include <queue>
using namespace std;

int main(){
	queue<char> p;
	cout << p.size() << endl;
	for(int i=0;i<10000;i++){
		int val = p.front();
		p.pop();
		cout << "i: " << i << " " << val << endl;
	}
	return 0;
}
