//
// Created by Charliegu on 2023/5/16.
//

#include "CacheManager.h"

CacheManager::CacheManager(size_t capacity) : capacity_(capacity) {}

string CacheManager::get(const string& key) {
    lock_guard<mutex> lock(mtx_);
    auto it = cacheMap_.find(key);
    if (it == cacheMap_.end()) {
        // 缓存中没有该数据，返回空字符串
        return "";
    } else {
        // 将数据移到链表头部
        moveToFront(it);
        return it->second->second;
    }
}

void CacheManager::write(const string& key, const string& value) {
    lock_guard<mutex> lock(mtx_);
    auto it = cacheMap_.find(key);
    if (it != cacheMap_.end()) {
        // 数据已经存在，更新值并移到链表头部
        it->second->second = value;
        moveToFront(it);
    } else {
        // 插入新的数据
        cache_.emplace_front(make_pair(key, value));
        cacheMap_[key] = cache_.begin();

        // 如果超过容量，移除链表尾部的元素
        if (cacheMap_.size() > capacity_) {
            evict();
        }
    }
}

void CacheManager::moveToFront(const MapType::iterator& it) {
    auto cacheIt = it->second;
    cache_.splice(cache_.begin(), cache_, cacheIt);
    cacheMap_[it->first] = cache_.begin();
}

void CacheManager::evict() {
    auto last = cache_.end();
    --last;
    cacheMap_.erase(last->first);
    cache_.pop_back();
}
