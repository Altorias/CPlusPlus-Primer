/*
Created by Charliegu on 2023/5/6.
编写一个my_vector类,模拟实现vector
1. 不用模板,只需要支持int
2. 支持动态扩容
3. 支持以下接口:
    1. push_back
    2. pop_back
    3. push_front
    4. pop_front
    5. size
    6. capacity
    7. 下标操作
    8. 互相赋值操作

-----
 1. 当有指针作为数据成员时，就需要写析构函数，将构造函数中new的空间释放掉
*/

#include <iostream>

using namespace std;

class my_vector {
public:
    // 构造函数
    my_vector() : size(0), capacity(2), data(new int[capacity]) {}

    // 析构函数
    ~my_vector() = default;
//    ~my_vector() { delete[] data; }

    // push_back
    // 添加元素到末尾
    void push_back(int number) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = number;
    }

    // pop_back
    // 弹出末尾的元素
    int pop_back() {
        if (size > 0) {
            int num = data[size - 1];
            size--;
            return num;
        }
        return -1;
    }

    // push_front
    // 添加元素到头部
    void push_front(int number) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        for (int i = size; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = number;
        size++;
    }

    // pop_front
    // 弹出头部元素
    int pop_front() {
        if (size > 0) {
            int number = data[0];
            for (int i = 0; i < size - 1; ++i) {
                data[i] = data[i + 1];
            }
            size--;
            return number;
        }
        return -1;
    }

    // 返回 vector 的大小
    int get_size() {
        return size;
    }

    // 返回 vector 的容量
    int get_capacity() {
        return capacity;
    }

    // 下标操作
    int &operator[](int index) { return data[index]; }

    // 互相赋值
    // 互相赋值操作
    my_vector &operator=(const my_vector &other) {
        if (this == &other) return *this;
        else {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new int[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            return *this;
        }
    }


private:
    // 数据存储空间
    int size;
    // 物理地址空间
    int capacity;
    // 指向数据的指针
    int *data;

    void resize(int new_capacity) {
        // 开辟新的内存空间
        int *new_data = new int[new_capacity];
        // 赋值
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        // 回收旧的空间
        delete[] data;
        // 更新数据
        data = new_data;
        capacity = new_capacity;
    }
};


int main() {
    my_vector mv;
    int num;
    cout << "向vector中输入元素，以-1结束" << endl;
    do {
        cin >> num;
        if (num != -1) {
            mv.push_back(num);
        }
    } while (num != -1);
    cout << "vector size: " << mv.get_size() << ", capacity: " << mv.get_capacity() << endl;
    cout << "vector elements: ";
    for (int i = 0; i < mv.get_size(); ++i) {
        cout << mv[i] << " ";
    }
    cout << endl;

    // 弹出末尾元素
    int res_tail = mv.pop_back();
    cout << "弹出末尾元素" << endl;
    cout << "pop_number:" << res_tail << endl;
    cout << "vector size: " << mv.get_size() << ", capacity: " << mv.get_capacity() << endl;
    for (int i = 0; i < mv.get_size(); ++i) {
        cout << mv[i] << " ";
    }
    cout << endl;

    // 添加元素到头部
    mv.push_front(98);
    cout << "添加元素到头部" << endl;
    cout << "vector size: " << mv.get_size() << ", capacity: " << mv.get_capacity() << endl;
    cout << "vector elements: ";
    for (int i = 0; i < mv.get_size(); ++i) {
        cout << mv[i] << " ";
    }
    cout << endl;


    // 弹出头部元素
    int res_head = mv.pop_front();
    cout << "弹出头部元素" << endl;
    cout << "pop_number:" << res_head << endl;
    cout << "vector size: " << mv.get_size() << ", capacity: " << mv.get_capacity() << endl;
    for (int i = 0; i < mv.get_size(); ++i) {
        cout << mv[i] << " ";
    }
    cout << endl;

    // 下标操作
//    cout << "vector[0]: " << mv[0] << endl;

// 互相赋值操作
    cout << "互相赋值操作" << endl;
    my_vector mv2 = mv;
    cout << "vector2 size: " << mv2.get_size() << ", capacity: " << mv2.get_capacity() << endl;
    cout << "vector2 elements: ";
    for (int i = 0; i < mv2.get_size(); ++i) {
        cout << mv2[i] << " ";
    }
    cout << endl;

    return 0;
}