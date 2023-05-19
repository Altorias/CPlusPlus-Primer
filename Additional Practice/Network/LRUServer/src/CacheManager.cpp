//
// Created by Charliegu on 2023/5/15.
//

#include "CacheManager.h"

CacheManager::CacheManager() {}

CacheManager::CacheManager(int capacity) : capacity_(capacity) {}

CacheManager::~CacheManager() = default;

void CacheManager::MoveToFront(const MapType::iterator &it) {
    auto cacheIt = it->second;
    cache_.splice(cache_.begin(), cache_, cacheIt);
    cacheMap_[it->first] = cache_.begin();
}

void CacheManager::Evict() {
    auto last = cache_.end();
    --last;
    cacheMap_.erase(last->first);
    cache_.pop_back();
}

bool CacheManager::Get(const std::string &key, std::string &value, Logger *logger, const int seq) {
    if (key.empty()) {
        logger->WriteLogError(LOCATION(), "从缓存中查询数据时不能为空 [seq=" + std::to_string(seq) + "]");
        return false;
    }
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = cacheMap_.find(key);
    if (it == cacheMap_.end()) {
        // 缓存中没有该数据，返回空字符串
        value = "";
    } else {
        // 将数据移到链表头部
        MoveToFront(it);
        value = it->second->second;
    }
    if (value.empty()) {
        logger->WriteLogDebug(LOCATION(),
                              "在缓存中查询key=[" + key + "]的记录，没有搜索到相应的记录 [seq=" + std::to_string(seq) +
                              "]");
    } else {
        logger->WriteLogDebug(LOCATION(),
                              "在缓存中查询key=[" + key + "]的记录，其value=[" + value + "] [seq=" +
                              std::to_string(seq) + "]");
    }
    return true;
}

bool CacheManager::Write(const std::string &key, const std::string &value, Logger *logger, const int seq) {
    if (key.empty() || value.empty()) {
        logger->WriteLogError(LOCATION(),
                              "往缓存中写入数据时key和value都不能为空，key=[" + key + "]，value=[" + value + "] [seq=" +
                              std::to_string(seq) + "]");
        return false;
    }
    std::lock_guard<std::mutex> lock(mtx_);
    auto it = cacheMap_.find(key);
    if (it != cacheMap_.end()) {
        std::string old_value = it->second->second;
        // 数据已经存在，更新值并移到链表头部
        it->second->second = value;
        MoveToFront(it);
        logger->WriteLogDebug(LOCATION(),
                              "往缓存中写入key=[" + key + "]，value=[" + value + "]的记录，其原来数据为key=[" + key +
                              "]，value=[" + old_value + "] [seq=" +
                              std::to_string(seq) + "]");
    } else {
        // 如果超过容量，移除链表尾部的元素
        if (cacheMap_.size() >= capacity_) {
            Evict();
        }
        // 插入新的数据
        cache_.emplace_front(make_pair(key, value));
        cacheMap_[key] = cache_.begin();
        logger->WriteLogDebug(LOCATION(),
                              "往缓存中写入key=[" + key + "]，value=[" + value + "]的记录 [seq=" +
                              std::to_string(seq) + "]");
    }
    return true;
}

/**
 * 重载运算符
 * （忘了有啥用了，之前有个BUG和这个有关，是由于mutex锁导致该对象无法被复制，因此使用此方法）
 * @param other
 * @return
 */
CacheManager &CacheManager::operator=(const CacheManager &other) {
    {
        if (&other != this) {
// lock both objects
            std::unique_lock<std::mutex> lock_this(mtx_, std::defer_lock);
            std::unique_lock<std::mutex> lock_other(other.mtx_, std::defer_lock);
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
}



