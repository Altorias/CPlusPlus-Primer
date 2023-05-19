//
// Created by Charliegu on 2023/5/18.
//
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main(){
    while (true){
        int opr = 0;
        string method;
        string key;
        string value;

        cout << "请输入操作类别: " << endl;
        cout << "1 - Get" << endl;
        cout << "2 - Write" << endl;
        cout << "-1 - Quit" << endl;
        cin >> opr;
        cin.ignore();

        if (opr == -1) {
            method = "quit";
        } else if (opr == 1) {
            method = "get";
            cout << "请输入key: " << endl;
            getline(cin, key);
            if (key.empty()) {
                cout << "key不能为空" << endl;
                continue;
            }
        } else if (opr == 2) {
            method = "write";
            cout << "请输入key: " << endl;
            getline(cin, key);
            if (key.empty()) {
                cout << "key不能为空" << endl;
                continue;
            }
            cout << "请输入value: " << endl;
            getline(cin, value);
            if (value.empty()) {
                cout << "value不能为空" << endl;
                continue;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入有误，请重新输入" << endl;
            continue;
        }
    }
}