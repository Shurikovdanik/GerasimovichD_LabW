#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <thread>
#include "../include/ThreadTunnel.h"

using namespace std::chrono_literals;

TEST(ThreadTunnelTest, MessageIsHandled) {
    ThreadTunnel tunnel;
    std::atomic<int> counter{0};

    tunnel.start([&counter](const std::string& msg) {
        if (msg == "ping") {
            counter++;
        }
    });

    tunnel.send("ping");
    tunnel.send("ping");

    std::this_thread::sleep_for(100ms);
    tunnel.stop();

    EXPECT_EQ(counter.load(), 2);
}

TEST(ThreadTunnelTest, StopPreventsFurtherHandling) {
    ThreadTunnel tunnel;
    std::atomic<int> counter{0};

    tunnel.start([&counter](const std::string& msg) {
        counter++;
    });

    tunnel.send("first");
    std::this_thread::sleep_for(50ms);
    tunnel.stop(); //Тут что-то не так?
    tunnel.send("second"); 

    std::this_thread::sleep_for(50ms);
    EXPECT_EQ(counter.load(), 1);
}

TEST(ThreadTunnelTest, HandlerIsCalled) {
    ThreadTunnel tunnel;
    std::atomic<bool> called{false};

    tunnel.start([&called](const std::string& msg) {
        called = true;
    });

    tunnel.send("hello");
    std::this_thread::sleep_for(50ms);
    tunnel.stop();

    EXPECT_TRUE(called.load());
}

TEST(ThreadTunnelTest, MultipleMessagesAreHandled) { //FAILED TEST -- needs to look up
    ThreadTunnel tunnel;
    std::atomic<int> count{0};

    tunnel.start([&count](const std::string& msg) {
        count += std::stoi(msg);
    });

    tunnel.send("1");
    tunnel.send("2");
    tunnel.send("3");

    std::this_thread::sleep_for(100ms);
    tunnel.stop();

    EXPECT_EQ(count.load(), 6);
}
