//
// Created by Charliegu on 2023/5/17.
//

#include "ServerResourceQueue.h"

ServerResourceQueue::ServerResourceQueue(): max_capacity_(0)  {}

ServerResourceQueue::~ServerResourceQueue() = default;

void ServerResourceQueue::Init(int max_capacity) {
    max_capacity_ = max_capacity;
}

void ServerResourceQueue::WaitTillPush(ResourceUnit &unit) {
    std::unique_lock<std::mutex> lock(mtx_);
    cv_full_.wait(lock, [this]() { return ts_queue_.size() < max_capacity_; });
    ts_queue_.push(unit);
    lock.unlock();
    cv_empty_.notify_one();
}

void ServerResourceQueue::WaitTillPop(ResourceUnit &unit) {
    std::unique_lock<std::mutex> lock(mtx_);
    cv_empty_.wait(lock, [this]() { return !ts_queue_.empty(); });
    unit = ts_queue_.front();
    ts_queue_.pop();
    lock.unlock();
    cv_full_.notify_one();
}