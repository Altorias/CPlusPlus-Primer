//
// Created by Charliegu on 2023/5/15.
//

#ifndef LRUSERVER_CACHEMANAGER_H
#define LRUSERVER_CACHEMANAGER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <mutex>
#include "Logger.h"

class CacheManager {
private:
    // 定义类型
    // 列表类型-双向链表
    typedef std::list<std::pair<std::string, std::string>> ListType;
    // Map类型-HashTable
    typedef std::unordered_map<std::string, ListType::iterator> MapType;

    // 容量
    int capacity_;
    // 缓存队列
    ListType cache_;
    // 缓存表
    MapType cacheMap_;
    // 锁
    mutable std::mutex mtx_;

    void MoveToFront(const MapType::iterator& it);
    void Evict();

public:
    CacheManager();
    CacheManager(int capacity);
    ~CacheManager();

    // 从缓存中获取数据
    bool Get(const std::string& key, std::string& value, Logger* logger,const int seq);

    // 将数据存入缓存
    bool Write(const std::string& key, const std::string& value, Logger* logger,const int seq);

    CacheManager& operator=(CacheManager const& other);

};


#endif //LRUSERVER_CACHEMANAGER_H
