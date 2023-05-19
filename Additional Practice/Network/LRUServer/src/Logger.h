//
// Created by Charliegu on 2023/5/15.
//

#ifndef LRUSERVER_LOGGER_H
#define LRUSERVER_LOGGER_H


#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <ctime>
#include <string>

#define LOCATION() \
   ("[" + (std::string(__FILE__) + ":" + std::to_string(__LINE__)) + "]")

enum class LogLevel {
    DEBUG,
    WARNING,
    ERROR,
};

class Logger {
private:
    // 文件流
    std::ofstream file_stream_;
    // 互斥锁
    std::mutex mtx_;

    void WriteLog(LogLevel level, const std::string& log_marco, const std::string& message);


public:
    Logger();
    Logger(const std::string& filename);
    virtual ~Logger();

    void WriteLogDebug(const std::string& log_marco, const std::string& message);

    void WriteLogWarning(const std::string& log_marco, const std::string& message);

    void WriteLogError(const std::string& log_marco, const std::string& message);


};

#endif //LRUSERVER_LOGGER_H

