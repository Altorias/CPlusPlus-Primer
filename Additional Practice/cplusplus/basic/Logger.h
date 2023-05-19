//
// Created by Charliegu on 2023/5/15.
//

#ifndef LRUSERVER_LOGGER_H
#define LRUSERVER_LOGGER_H
#define LOCATION() \
   ("[" + (std::string(__FILE__) + ":" + std::to_string(__LINE__)) + "]")


#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

class Logger {
public:
    Logger(const std::string& filename);
    virtual ~Logger();

    void log(LogLevel level, const std::string& message);

private:
    std::ofstream m_file;
    std::mutex m_mutex;
};


#endif //LRUSERVER_LOGGER_H

