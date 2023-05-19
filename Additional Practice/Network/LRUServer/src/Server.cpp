#include "Server.h"


Server::Server() {
    seq_ = 0;
    port_logger_ = nullptr;
    opr_logger_ = nullptr;
    cache_manager_ = nullptr;
    port_ = 0;
    address_ = "";
    server_resource_queue_capacity_ = 0;
    cache_capacity_ = 0;
    consumer_threads_ = 0;
    buffer_size_ = 0;
    port_logger_file_path_ = "";
    opr_logger_file_path_ = "";
}

bool Server::Init(const std::string &conf_file) {
    Json::Reader json_reader;
    Json::Value root;
    std::ifstream in(conf_file, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "打开文件失败:" + conf_file << std::endl;
        return false;
    }
    if (!json_reader.parse(in, root)) {
        std::cerr << "解析文件失败:" + conf_file << std::endl;
        return false;
    } else {
        seq_ = root["seq"].asInt();
        port_ = root["port"].asInt();
        buffer_size_ = root["bufferSize"].asInt();
        address_ = root["address"].asString();
        server_resource_queue_capacity_ = root["resourceCapacity"].asInt();
        cache_capacity_ = root["cacheCapacity"].asInt();
        consumer_threads_ = root["consumerThreads"].asInt();
        port_logger_file_path_ = root["portLogFilePath"].asString();
        opr_logger_file_path_ = root["oprLogFilePath"].asString();
    }
    port_logger_ = new Logger(port_logger_file_path_);
    opr_logger_ = new Logger(opr_logger_file_path_);
    cache_manager_ = new CacheManager(cache_capacity_);
    server_resource_queue_ = new ServerResourceQueue();
    server_resource_queue_->Init(server_resource_queue_capacity_);
    return true;
}

bool Server::StartServer() {
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    char ip[128] = {0};
    if (server_socket_ == -1) {
        std::cerr << "创建socket失败 " << std::endl;
        return false;
    }

    // 初始化socket信息
    struct sockaddr_in server_address{};
    server_address.sin_family = AF_INET;

    inet_pton(AF_INET, address_.c_str(), &server_address.sin_addr);
    server_address.sin_port = htons(port_);


    if (bind(server_socket_, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        std::cerr << "绑定ip地址失败 " << std::endl;
        return false;
    }

    if (listen(server_socket_, 4) < 0) {
        std::cerr << "监听端口失败 " << std::endl;
        return false;
    }

    std::cout << "服务器启动于:" << inet_ntop(AF_INET, &server_address.sin_addr, ip, 128) << ":"
              << ntohs(server_address.sin_port) << std::endl;
    std::cout << "等待连接 " << std::endl;
    return true;
}

void Server::Quit() const {
    close(server_socket_);
}

void Server::Run() {
    // 初始化

    auto *_network = new Network();
    std::vector<std::thread> consumer_threads_vector;


    // 创建消费者线程
    for (int i = 0; i < consumer_threads_; ++i) {
        auto *request_handler = new RequestHandler();
        std::thread t(&RequestHandler::HandleResourceQueue, request_handler, server_resource_queue_, opr_logger_,
                      cache_manager_);
        consumer_threads_vector.push_back(std::move(t));
    }


    for (auto &t: consumer_threads_vector) {
        t.detach();
    }

    // Start the server and accept connections
    if (!StartServer()) {
        std::cerr << "服务器启动失败" << std::endl;
    } else {
        _network->Init(server_socket_, seq_, buffer_size_);
        std::thread t(&Network::AcceptConnections, _network, server_resource_queue_, port_logger_);
        t.join();
    }

}

