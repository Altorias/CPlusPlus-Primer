//
// Created by Charliegu on 2023/5/15.
//
#include "Logger.h"
#include <chrono>
#include <ctime>

Logger::Logger(const std::string& filename) {
    m_file.open(filename, std::ios_base::out | std::ios_base::app);
}

Logger::~Logger() {
    m_file.close();
}

void Logger::log(LogLevel level, const std::string& message) {
    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    // Format log message
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    std::string level_str;
    switch (level) {
        case LogLevel::TRACE:
            level_str = "TRACE";
            break;
        case LogLevel::DEBUG:
            level_str = "DEBUG";
            break;
        case LogLevel::INFO:
            level_str = "INFO";
            break;
        case LogLevel::WARNING:
            level_str = "WARNING";
            break;
        case LogLevel::ERROR:
            level_str = "ERROR";
            break;
        case LogLevel::FATAL:
            level_str = "FATAL";
            break;
        default:
            level_str = "UNKNOWN";
            break;
    }
    std::string log_message = "[" + std::string(buffer) + "] " + level_str + ": " + message + "\n";

    // Write log message to file
    std::lock_guard<std::mutex> lock(m_mutex);
    m_file << log_message;
    m_file.flush();
}