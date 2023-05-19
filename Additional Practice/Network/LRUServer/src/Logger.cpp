//
// Created by Charliegu on 2023/5/15.
//
#include "Logger.h"

Logger::Logger() {}
Logger::Logger(const std::string& filename) {
    file_stream_.open(filename, std::ios_base::out | std::ios_base::app);
}

Logger::~Logger() {
    file_stream_.close();
}

void Logger::WriteLog(LogLevel level, const std::string& log_marco, const std::string& message) {
    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    // Format log message
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    std::string level_str;
    switch (level) {
        case LogLevel::DEBUG:
            level_str = "DEBUG";
            break;
        case LogLevel::WARNING:
            level_str = "WARNING";
            break;
        case LogLevel::ERROR:
            level_str = "ERROR";
            break;
    }
    std::string log_message = "[" + std::string(buffer) + "]" + log_marco + " " + level_str + " : " + message + "\n";

    {
        // Write log message to file
        std::lock_guard<std::mutex> lock(mtx_);
        file_stream_ << log_message;
        file_stream_.flush();
    }
}


void Logger::WriteLogDebug(const std::string &log_marco, const std::string &message) {
    WriteLog(LogLevel::DEBUG,log_marco,message);
}

void Logger::WriteLogWarning(const std::string &log_marco, const std::string &message) {
    WriteLog(LogLevel::WARNING,log_marco,message);
}

void Logger::WriteLogError(const std::string &log_marco, const std::string &message) {
    WriteLog(LogLevel::ERROR,log_marco,message);
}