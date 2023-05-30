//
// Created by Charliegu on 2023/5/30.
//

#include<iostream>
using namespace std;

int main(){
    int low,high;
    cout << "please input number, divide by space" << endl;
    cin >> low >> high;
    for (int i = low; i <= high ; ++i) {
        cout << i << endl;
    }
    return 0;
}