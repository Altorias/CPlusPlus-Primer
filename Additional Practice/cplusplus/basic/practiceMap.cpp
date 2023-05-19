/*
Created by Charliegu on 2023/5/6.
编写一个程序，实现一个英文单词计数器，统计一个文本文件中每个单词出现的次数，并按照出现次数从大到小输出结果。
 -----
 1. IO流读取文件
 2. 单词可能以空格或者句号"."结束，有可能包含"-"，有可能被""双引号包裹
 3. 大小写问题，把每个单词都变成小写
 4. 假设输入的单词都是合法的

*/

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

bool compare(pair<string, int>& a, pair<string, int>& b){
    if (a.second == b.second){
        return a.first > b.first;
    }
    return a.second > b.second;
}

int main(){
    string file_name;
    map<string, int> word_count;
    string word;
    cout << "请输入文件名" << endl;
    cin >> file_name;
    ifstream fin;
    fin.open(file_name, ios::in);
    if (!fin.is_open()){
        cout << "打开文件失败" << endl;
        return 0;
    }
    // 读取未知数量的string对象
    while(fin >> word){
//      这个方法可以将单词变成小写
//      transform(word.begin(), word.end(), word.begin(), ::tolower);
//      这个方法可以去除标点符号
//      word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        string real_word;
        for (auto c:word){
            // 如果不是英文字母就跳过
            if (!isalpha(c)){
                continue;
            }
            real_word.push_back(::tolower(c));
        }
        if (!real_word.empty()) {
            word_count[real_word]++;
        }
    }
    // 对map进行排序,C++默认是按照key排序，如果要按照value排序，需要将数据以pair的形式放到vector中，并对vector进行排序。
    // 将统计结果存入 vector 中
    vector<pair<string, int>> word_pair(word_count.begin(), word_count.end());

    // 对 vector 按照单词出现次数排序
    sort(word_pair.begin(), word_pair.end(), compare);

    // 输出统计结果
    for (auto& pair : word_pair) {
        cout << pair.first << " " << pair.second << endl;
    }

    return 0;

}
