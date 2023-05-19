//
// Created by Charliegu on 2023/5/16.
//
#include <iostream>
#include <string>
#include "Logger.h"
using namespace std;




void print(const string& s, string info){
    cout << s << info << endl;
}

int main(){
    print(LOCATION(), "12332" );
}