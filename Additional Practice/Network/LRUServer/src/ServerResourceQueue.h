//
// Created by Charliegu on 2023/5/17.
//

// 服务器资源队列（生产者消费者模型队列）

#ifndef LRUSERVER_SERVERRESOURCEQUEUE_H
#define LRUSERVER_SERVERRESOURCEQUEUE_H


#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>

struct ResourceUnit{
    // seq流水号
    int seq;
    // 用户socketID
    int client_socket_id;
    // 用户传递的字符串
    std::string json;
};

//template <typename T>
class ServerResourceQueue{
private:
    // 最大容量
    int max_capacity_;
    // 队列
    std::queue<ResourceUnit> ts_queue_;
    // 条件变量空
    std::condition_variable cv_empty_;
    // 条件变量满
    std::condition_variable cv_full_;
    // 互斥锁
    std::mutex mtx_;

public:
    // 构造函数
    ServerResourceQueue() ;

    // 析构函数
    ~ServerResourceQueue() ;

    void Init(int max_capacity);

    void WaitTillPush(ResourceUnit& unit);

    void WaitTillPop(ResourceUnit& unit) ;
};


#endif //LRUSERVER_SERVERRESOURCEQUEUE_H
