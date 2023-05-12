/*
Created by Charliegu on 2023/5/6.
编写一个程序，实现将两个list按顺序合并，并输出合并后的list。
------
 1. list是双向链表
 2. 默认list是有序的？
 3. 要求按顺序合并而不是合并后排序
 4. 使用双指针解决

*/
#include <iostream>
#include <list>
using namespace std;

int main(){
    list<int> list0, list1, resList;
    int num;

    // 输入第一个 list 的元素
    cout << "请输入第一个 list 的元素，以 -1 结束：" << endl;
    while (true) {
        cin >> num;
        if (num == -1) break;
        list0.push_back(num);
    }

    // 输入第二个 list 的元素
    cout << "请输入第二个 list 的元素，以 -1 结束：" << endl;
    while (true) {
        cin >> num;
        if (num == -1) break;
        list1.push_back(num);
    }

    // 合并两个 list 并排序
    auto i = list0.begin(), j = list1.begin();
    while(i != list0.end() && j != list1.end()){
        if (*i < *j) {
            resList.push_back(*i);
            i++;
        } else {
            resList.push_back(*j);
            j++;
        }
    }
    while ( i != list0.end()){
        resList.push_back(*i);
        i++;
    }
    while ( j != list1.end()){
        resList.push_back(*j);
        j++;
    }


    // 输出合并后的 list
    cout << "合并后的 list 为：" << endl;
    for (auto const &i: resList) {
        std::cout << i << " ";
    }
    cout << endl;

    return 0;
    cout << "hello" <<endl;
    return 0;
}