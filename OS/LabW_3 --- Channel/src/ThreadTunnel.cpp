#include "../include/ThreadTunnel.h"
#include <iostream>
ThreadTunnel::ThreadTunnel() = default;

ThreadTunnel::~ThreadTunnel() {
    stop();
}

void ThreadTunnel::start(Handler handler) {
    if (running_) return;
    handler_ = std::move(handler);
    running_ = true;
    writer_ = std::thread(&ThreadTunnel::writerLoop, this);
    reader_ = std::thread(&ThreadTunnel::readerLoop, this);
}

void ThreadTunnel::stop() {
    bool expected = true;
    if (!running_.compare_exchange_strong(expected, false)) {
        return; 
    }
    cv_.notify_all();

    if (writer_.joinable()) writer_.join();
    if (reader_.joinable()) reader_.join();
}

void ThreadTunnel::send(std::string msg) {
    {
        std::lock_guard<std::mutex> lock(mtx_);
        queue_.push(std::move(msg));
    }
    cv_.notify_one();
}

void ThreadTunnel::writerLoop() {
    using namespace std::literals::chrono_literals;
    int counter = 0;
    while (running_) {
        send("msg #" + std::to_string(counter++));
        std::this_thread::sleep_for(200ms);
    }
}

void ThreadTunnel::readerLoop() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [&] {
            return !running_ ? true : !queue_.empty();
        });

        if (!running_ && queue_.empty()) {
            break; 
        }

        while (!queue_.empty()) {
            auto msg = std::move(queue_.front());
            queue_.pop();
            lock.unlock();

            if (handler_) {
                handler_(msg);
            } else {
                std::cout << "[Tunnel] " << msg << "\n";
            }

            lock.lock();
        }
    }
}
