//
// Created by Charliegu on 2023/5/16.
//

#ifndef CPLUSPLUS_PRIMER_CACHEMANAGER_H
#define CPLUSPLUS_PRIMER_CACHEMANAGER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <mutex>
using namespace std;

class CacheManager {
public:
    CacheManager(size_t capacity);

    // 从缓存中获取数据
    string get(const string& key);

    // 将数据存入缓存
    void write(const string& key, const string& value);

    CacheManager& operator=(CacheManager const& other){
        if(&other != this)
        {
// lock both objects
            unique_lock<mutex> lock_this(mtx_, defer_lock);
            unique_lock<mutex> lock_other(other.mtx_, defer_lock);

// ensure no deadlock
            lock(lock_this, lock_other);

// safely copy the data
            capacity_ = other.capacity_;
            cache_ = other.cache_;
            cacheMap_ = other.cacheMap_;

// ... etc...
        }

        return *this;

    }


private:
    typedef list<pair<string, string>> ListType;
    typedef unordered_map<string, ListType::iterator> MapType;

    void moveToFront(const MapType::iterator& it);

    void evict();

    size_t capacity_;
    ListType cache_;
    MapType cacheMap_;
    mutable mutex mtx_;
};



#endif //CPLUSPLUS_PRIMER_CACHEMANAGER_H
