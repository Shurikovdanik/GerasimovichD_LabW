#include "../include/ThreadTunnelUnit.h"
#include <iostream>
#include "../include/ThreadEvent.h"
#include "Matrix.h"
template class ThreadTunnelUnit<std::string>;
template class ThreadTunnelUnit<int>;
template class ThreadTunnelUnit<Matrix>;
template class ThreadTunnelUnit<int,int>;
template class ThreadTunnelUnit<std::tuple<int,int>>;

template <typename... Args>
ThreadTunnelUnit<Args...>::ThreadTunnelUnit()
    : writer_{custom::Thread(std::bind(&ThreadTunnelUnit::writerLoop, this))}, reader_{custom::Thread(std::bind(&ThreadTunnelUnit::readerLoop, this))}, running_{false}, handler_{}
{
}
template <typename... Args>
ThreadTunnelUnit<Args...>::~ThreadTunnelUnit()
{
    stop();
}
template <typename... Args>
void ThreadTunnelUnit<Args...>::start(Handler handler)
{
    if (running_)
        return;

    handler_ = std::move(handler);
    running_ = true;

    writer_ = custom::Thread(&ThreadTunnelUnit::writerLoop, this);

    writer_.addEventListener(new custom::ThreadFinEvent(), [this]() {});

    writer_.start();

    reader_ = custom::Thread(&ThreadTunnelUnit::readerLoop, this);
    reader_.start();
}
template <typename... Args>
void ThreadTunnelUnit<Args...>::stop()
{
    bool expected = true;
    if (!running_.compare_exchange_strong(expected, false))
    {
        return;
    }

    {
        std::lock_guard<std::recursive_mutex> lock(clMtx_);
        std::queue<std::tuple<Args...>> empty;
        std::swap(queue_, empty);
    }

    cv_.notify_all();

    writer_.join();
    reader_.join();
}

template <typename... Args>
void ThreadTunnelUnit<Args...>::send(Args... args)
{
    {
        std::lock_guard<std::mutex> lock(mtx_);
        queue_.emplace(std::make_tuple(std::forward<Args>(args)...));
    }
    cv_.notify_one();
}

template <typename... Args>
void ThreadTunnelUnit<Args...>::send(std::tuple<Args...> tup)
{
    {
        std::lock_guard<std::mutex> lock(mtx_);
        queue_.emplace(std::move(tup));
    }
    cv_.notify_one();
}

template <typename... Args>
void ThreadTunnelUnit<Args...>::writerLoop()
{
    using namespace std::literals::chrono_literals;
    int counter = 0;
    bool isGeneratingDefaultMessages_ = false;
    while (running_)
    {
        if constexpr (sizeof...(Args) == 1 &&
                      std::is_same_v<std::tuple_element_t<0, std::tuple<Args...>>, std::string>)
        {
            if (isGeneratingDefaultMessages_)
                send("msg #" + std::to_string(counter++));
        }
        std::this_thread::sleep_for(200ms);
    }
}

template <typename... Args>
void ThreadTunnelUnit<Args...>::readerLoop()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [&]
                 { return !running_ || !queue_.empty(); });

        if (!running_ && queue_.empty())
            break;

        while (!queue_.empty())
        {
            auto argsTuple = std::move(queue_.front());
            queue_.pop();
            lock.unlock();

            if (handler_)
            {
                std::apply(handler_, argsTuple);
            }
            else
            {
                if constexpr (sizeof...(Args) == 1 &&
                              std::is_same_v<std::tuple_element_t<0, std::tuple<Args...>>, std::string>)
                {
                    std::cout << "[Tunnel] " << std::get<0>(argsTuple) << "\n";
                }
            }

            lock.lock();
        }
    }
}