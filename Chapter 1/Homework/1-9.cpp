//
// Created by Charliegu on 2023/5/30.
//
#include <iostream>
using namespace std;

int main() {
    int i = 50;
    int sum = 0;
    while (i < 101) {
        sum += i;
        i++;
    }
    cout << sum << endl;
    return 0;
}