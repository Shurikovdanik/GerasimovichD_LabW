#pragma once
#include <map>
#include <string>
#include "ThreadTunnelUnit.h"
#include <shared_mutex>
#include <tuple>
template <typename T>
class ThreadTunnel
{
public:
    void addThread(const std::string &name, std::function<void(const T &)> handler)
    {
        std::unique_lock lock(mutex_);
        threads.try_emplace(name);
        threads[name].start(std::move(handler));
    }
    void send(const T &msg)
    {
        std::shared_lock lock(mutex_);
        int minQueue = -1;
        std::string minName;
        for (auto &[name, cur] : threads)
        {
            if (minQueue == -1 || cur.queueLength() < minQueue)
            {
                minQueue = cur.queueLength();
                minName = name;
                continue; 
            }
            if (minQueue > cur.queueLength()) {
                minQueue = cur.queueLength();
                minName = name;
                continue; 
            }
        }
        sendDataByName(minName, msg);
    }
    void sendDataByName(const std::string &name, const T &msg)
    {
        std::shared_lock lock(mutex_);
        auto it = threads.find(name);
        if (it != threads.end())
        {
            it->second.send(std::make_tuple(msg));
        }
    }
    ThreadTunnel() = default;
    ThreadTunnel(const ThreadTunnel &) = delete;
    ThreadTunnel &operator=(const ThreadTunnel &) = delete;

private:
    // Разрешено множественное чтение - но не запись
    mutable std::shared_mutex mutex_;
    std::map<std::string, ThreadTunnelUnit<T>> threads;
};
