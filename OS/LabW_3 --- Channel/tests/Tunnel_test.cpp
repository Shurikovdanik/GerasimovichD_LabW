#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <thread>
#include "ThreadTunnelUnit.h"
#include "ThreadTunnel.h"
#include "Matrix.h"

constexpr auto TIMEOUT = std::chrono::milliseconds(200);

TEST(ThreadTunnelUnitTest, StartAndStopDoesNotCrash) {
    ThreadTunnelUnit<std::string> tunnel;
    tunnel.start([](const std::string&) {
        // no-op
    });
    tunnel.stop();
    SUCCEED();
}

TEST(ThreadTunnelUnitTest, SendMessageIsHandled) {
    ThreadTunnelUnit<std::string> tunnel;
    std::atomic<bool> handled{false};

    tunnel.start([&](const std::string& msg) {
        if (msg == "hello") {
            handled = true;
        }
    });

    tunnel.send(std::make_tuple("hello"));

    for (int i = 0; i < 10 && !handled; ++i) {
        std::this_thread::sleep_for(TIMEOUT);
    }

    //tunnel.stop();
    EXPECT_TRUE(handled);
}

TEST(ThreadTunnelUnitTest, MultipleMessagesHandled) {
    ThreadTunnelUnit<std::string> tunnel;
    std::vector<std::string> received;
    std::mutex m;

    tunnel.start([&](const std::string& msg) {
        std::lock_guard<std::mutex> lock(m);
        received.push_back(msg);
    });

    tunnel.send(std::make_tuple("one"));
    tunnel.send(std::make_tuple("two"));
    tunnel.send(std::make_tuple("three"));

    std::this_thread::sleep_for(TIMEOUT);
    tunnel.stop();

    std::lock_guard<std::mutex> lock(m);
    //EXPECT_EQ(received.size(), 3);
    EXPECT_EQ(received[0], "one");
    EXPECT_EQ(received[1], "two");
    EXPECT_EQ(received[2], "three");
}

TEST(ThreadTunnelTest, AddThreadAndSendString) {
    ThreadTunnel<std::string> tunnel;
    std::string received;

    tunnel.addThread("printer", [&](const std::string& msg) {
        received = msg;
    });

    tunnel.sendDataByName("printer", "hello");
    for (int i = 0; i < 3; ++i) { //lookout to default messages
        std::this_thread::sleep_for(TIMEOUT);
    }
    std::this_thread::sleep_for(TIMEOUT);
    EXPECT_EQ(received, "hello");
}

TEST(ThreadTunnelTest, SendToNonExistingThreadDoesNothing) {
    ThreadTunnel<std::string> tunnel;
    EXPECT_NO_THROW(tunnel.sendDataByName("ghost", "msg"));
}

// === Тесты для Matrix ===

TEST(ThreadTunnelTest, AddThreadAndSendMatrix) {
    ThreadTunnel<Matrix> tunnel;
    std::atomic<bool> handled{false};
    tunnel.addThread("matrixHandler", [&](const Matrix& m) { // Need to wait
        EXPECT_EQ(m.getDX(), 2);
        EXPECT_EQ(m.getDY(), 2);
        handled = true;
    });

    Matrix mat(2, 2);
    tunnel.sendDataByName("matrixHandler", mat);
    for (int i = 0; i < 10 && !handled; ++i) {
        std::this_thread::sleep_for(TIMEOUT);
    }
    EXPECT_TRUE(handled);
}

// === Тест на многопоточность ===

TEST(ThreadTunnelTest, ThreadSafetyUnderParallelAccess) {
    ThreadTunnel<int> tunnel;
    std::atomic<int> counter{0};

    tunnel.addThread("counter", [&](const int& v) {
        counter += v;
    });

    std::vector<std::thread> workers;
    for (int i = 0; i < 10; ++i) {
        workers.emplace_back([&] {
            for (int j = 0; j < 100; ++j) {
                tunnel.sendDataByName("counter", 1);
            }
        });
    }

    for (auto& t : workers) t.join();

    EXPECT_EQ(counter.load(), 1000);
}