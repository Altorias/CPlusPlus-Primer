/*
Created by Charliegu on 2023/5/8.
 编写一个my_queue类,模拟实现queue
1. 不用模板,只需要支持int
2. 支持动态扩容
3. 支持以下接口:
    1. front() 返回指向队首元素的引用
    2. back()  返回指向队尾元素的引用
    3. push()  向队列尾部插入数据
    4. pop()   弹出队列头部的数据
    5. size()  返回队列中元素个数
    6. empty() 检查队列是否为空，并返回布尔值
    7. swap()  交换两个队列的值
*/

#include <iostream>
using namespace std;

class my_queue{
public:
    my_queue(): queue_size(0),head(nullptr),tail(nullptr){}
    ~my_queue() {
        while(head != nullptr){
            queue_node* temp = head->next;
            delete head;
            head = temp;
        }
    }

    int& front() {
        return head->value;
    }

    int& back(){
        return tail->value;
    }

    void push(int number){
        queue_node* node = new queue_node(number);
        queue_size++;

        if (nullptr == head){
            head = node;
            tail = node;
        }else{
            tail->next = node;
            tail= node;
        }
    }

    void pop(){
        if (queue_size > 0){
            queue_node* temp = head->next;
            delete head;
            head = temp;
            queue_size--;
        }
    }

    int size(){
        return queue_size;
    }

    bool empty(){
        return queue_size == 0;
    }

    void swap(my_queue& other) {
        std::swap(queue_size, other.queue_size);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }


private:
    class queue_node {
    public:
        int value;
        queue_node* next;
        queue_node(int number): value(number), next(nullptr) {}
    };
    int queue_size;
    queue_node* head;
    queue_node* tail;

};

int main(){
    my_queue* mq = new my_queue();
    mq->push(1);
    mq->push(2);
    mq->push(3);
    mq->push(4);
    mq->push(5);
    cout<<"queue0 front number: "<<mq->front()<<endl;
    cout<<"queue0 back number: "<<mq->back()<<endl;
    cout<<"queue0 size: "<<mq->size()<<endl;
    mq->pop();
    mq->pop();
    cout<<"queue0 front number: "<<mq->front()<<endl;
    cout<<"queue0 back number: "<<mq->back()<<endl;
    cout<<"queue0 size: "<<mq->size()<<endl;
    cout<<endl;
    my_queue* mq1 = new my_queue();
    if (mq1->empty()){
        cout<<"queue1 is empty"<<endl;
    }
    mq1->push(-1);
    mq1->push(-2);
    mq1->push(-3);
    cout<<"queue1 front number: "<<mq1->front()<<endl;
    cout<<"queue1 back number: "<<mq1->back()<<endl;
    cout<<"queue1 size: "<<mq1->size()<<endl;

    mq->swap(*mq1);
    cout<<"queue0 front number: "<<mq->front()<<endl;
    cout<<"queue0 back number: "<<mq->back()<<endl;
    cout<<"queue0 size: "<<mq->size()<<endl;
    cout<<endl;

    cout<<"queue1 front number: "<<mq1->front()<<endl;
    cout<<"queue1 back number: "<<mq1->back()<<endl;
    cout<<"queue1 size: "<<mq1->size()<<endl;



    return 0;
}