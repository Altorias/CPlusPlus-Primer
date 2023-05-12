/*
Created by Charliegu on 2023/5/6.
编写一个函数，接受一个字符串作为参数，并删除字符串中的空格
 -----
1. 由于默认的cin输入字符串会在读到空格时停止，如" hello world " 会被裁剪为"hello",因此此处应该使用getline来读取一整行输入
*/


#include <iostream>
#include <string>
using namespace std;

string removeSpace(string str){
    if (str.empty()){
        return str;
    }
    string result;
    for(auto c:str){
        if (!isspace(c)){
            result+=c;
        }
    }
//    cout << result << endl;
    return result;
}

int main(){
    string str;
    cout << "please input string" << endl;
    getline(cin, str);
    if (!str.empty()){
        string res = removeSpace(str);
        cout << res << endl;
    }
    return 0;
}