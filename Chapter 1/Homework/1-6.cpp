//
// Created by Charliegu on 2023/5/11.
//
// 该程序不是合法的，因为 "<<" 需要跟在 cout/cin 之后.

#include <iostream>

using namespace std;

int main(){
    int v1 = 0,v2 = 0;
    cout << "Enter two numbers: " << endl;
    cin >> v1 >> v2;
    cout << "The product of " << v1;
    cout << " and " << v2;
    cout <<" is " << v1+v2 << endl;
    return 0;
}