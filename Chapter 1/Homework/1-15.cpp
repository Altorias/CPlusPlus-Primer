//
// Created by Charliegu on 2023/5/30.
//
#include <iostream>


int main() {
    // 错误1: 语法错误 - 缺少分号
    std::cout << "Hello, World!" << std::endl

    // 错误2: 类型错误 - 试图将字符串赋值给整型变量
    int number = "42";

    // 错误3: 语法错误 - 多余的右括号
    std::cout << "The answer is: " << number << ")" << std::endl;

    // 错误4: 声明错误 - 重复定义同一变量
    int number = 42;

    // 错误5: 使用未声明的变量
    std::cout << "Another number: " << anotherNumber << std::endl;

    // 错误6: 缺少返回值
    return;
}
