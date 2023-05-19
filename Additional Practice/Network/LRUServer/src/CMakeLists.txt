cmake_minimum_required(VERSION 3.20)
project(LRUServer)
#include_directories("D:/Library/jsoncpp1_9_5/include")
#include_directories("D:/Library/jsoncpp1_9_5/include/json")
#include_directories("D:/Library/jsoncpp1_9_5/lib")
#set(lib_DIR /usr/lib/x84_64-linux-gnu)
#find_package(${lib_DIR})
#target_link_libraries(LRUServer libjsoncpp.a)

set(CMAKE_CXX_STANDARD 11)
# add_executable(LRUServer src/main.cpp src/ServerResourceQueue.cpp src/ServerResourceQueue.h src/Logger.cpp src/Logger.h)

# target_link_libraries(LRUServer -ljsoncpp)
# target_link_libraries(LRUServer D:/Library/jsoncpp1_9_5/lib/libjsoncpp.a)


# 添加可执行文件的源代码
add_executable(${PROJECT_NAME} main.cpp
        ServerResourceQueue.cpp ServerResourceQueue.h
        Logger.cpp Logger.h
        CacheManager.cpp CacheManager.h
        RequestHandler.cpp RequestHandler.h
        ConnectionHandler.cpp ConnectionHandler.h
        Network.cpp Network.h
        Server.cpp Server.h)


## 设置日志文件目录
#set(LOG_DIR ../log)
#
## 配置编译时的宏定义，指定日志文件路径
#target_compile_definitions(${PROJECT_NAME} PRIVATE LOG_FILE="${LOG_DIR}/server.log")
target_link_libraries(LRUServer -ljsoncpp)
