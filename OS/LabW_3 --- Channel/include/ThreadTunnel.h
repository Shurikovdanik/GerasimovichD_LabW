#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <atomic>
#include <functional>
#include <chrono>

class ThreadTunnel {
public:
    using Handler = std::function<void(const std::string&)>;

    ThreadTunnel();
    ~ThreadTunnel();

    void start(Handler handler);

    void stop();

    void send(std::string msg);

    ThreadTunnel(const ThreadTunnel&) = delete;
    ThreadTunnel& operator=(const ThreadTunnel&) = delete;

private:
    void writerLoop();
    void readerLoop();

    std::thread writer_;
    std::thread reader_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::queue<std::string> queue_;
    std::atomic<bool> running_{false};

    Handler handler_{};
};
