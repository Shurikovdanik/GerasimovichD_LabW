#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <atomic>
#include <functional>
#include <chrono>
#include "Thread.h"
/**Потоковый буфферный туннель на 1 поток */
template<typename... Args>
class ThreadTunnelUnit {
public:
    using Handler = std::function<void(Args...)>;

    ThreadTunnelUnit();
    ~ThreadTunnelUnit();
    ThreadTunnelUnit(const ThreadTunnelUnit&) = delete;
    ThreadTunnelUnit& operator=(const ThreadTunnelUnit&) = delete;

    // Разрешаем перемещение
    ThreadTunnelUnit(ThreadTunnelUnit&&) noexcept = default;
    ThreadTunnelUnit& operator=(ThreadTunnelUnit&&) noexcept = default;
    int queueLength() const {return queue_.size();}
    void start(Handler handler);
    void stop();
    void send(std::tuple<Args...>);
private:
    void send(Args... args);
    custom::Thread writer_;
    custom::Thread reader_;
    void writerLoop();
    void readerLoop();
    std::mutex mtx_;
    std::recursive_mutex clMtx_;
    std::condition_variable cv_;
    std::queue<std::tuple<Args...>> queue_;
    std::atomic<bool> running_{false};
    Handler handler_{};
};
