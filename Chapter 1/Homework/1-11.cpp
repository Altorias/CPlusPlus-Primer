//
// Created by Charliegu on 2023/5/30.
//
#include<iostream>
using namespace std;

int main(){
    int low,high;
    cout << "please input two number, divide by space" << endl;
    cin >> low >> high ;
    while (low <= high) {
        cout << low++ << endl;
    }
    return 0;
}