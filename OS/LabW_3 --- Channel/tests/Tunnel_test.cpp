#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>
#include "BufferedChannel.h"
#include "Matrix.h"

constexpr auto TIMEOUT = std::chrono::milliseconds(200);

TEST(BufferedChannelTest, SendAndRecv) {
    BufferedChannel<std::string> channel(10);
    std::string received;
    std::atomic<bool> done{false};

    auto sender = std::thread([&]() {
        channel.Send("hello");
        done = true;
    });

    auto receiver = std::thread([&]() {
        auto [msg, ok] = channel.Recv();
        if (ok) {
            received = msg;
        }
        channel.Close();
    });

    sender.join();
    receiver.join();
    
    EXPECT_EQ(received, "hello");
}

TEST(BufferedChannelTest, MultipleMessages) {
    BufferedChannel<std::string> channel(10);
    std::vector<std::string> received;
    std::mutex m;

    auto receiver = std::thread([&]() {
        while (true) {
            auto [msg, ok] = channel.Recv();
            if (!ok) break;
            {
                std::lock_guard<std::mutex> lock(m);
                received.push_back(msg);
            }
        }
    });

    channel.Send("one");
    channel.Send("two");
    channel.Send("three");
    channel.Close();

    receiver.join();

    std::lock_guard<std::mutex> lock(m);
    EXPECT_EQ(received.size(), 3);
    EXPECT_EQ(received[0], "one");
    EXPECT_EQ(received[1], "two");
    EXPECT_EQ(received[2], "three");
}

TEST(BufferedChannelTest, ClosedChannelThrows) {
    BufferedChannel<std::string> channel(10);
    channel.Close();
    
    EXPECT_THROW(channel.Send("msg"), std::runtime_error);
}

// === Тесты для Matrix ===

TEST(BufferedChannelTest, SendAndRecvMatrix) {
    BufferedChannel<Matrix> channel(10);
    std::atomic<bool> handled{false};

    auto receiver = std::thread([&]() {
        auto [mat, ok] = channel.Recv();
        if (ok) {
            EXPECT_EQ(mat.getDX(), 2);
            EXPECT_EQ(mat.getDY(), 2);
            handled = true;
        }
        channel.Close();
    });

    Matrix mat(2, 2);
    channel.Send(mat);

    auto start = std::chrono::steady_clock::now();
    while (!handled && std::chrono::steady_clock::now() - start < TIMEOUT) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    if (!handled) channel.Close(); 
    receiver.join();

    EXPECT_TRUE(handled);
}

TEST(BufferedChannelTest, SendAndRecvMatrixWithJoin) {
    BufferedChannel<Matrix> channel(10);
    std::atomic<bool> handled{false};

    auto receiver = std::thread([&]() {
        auto [mat, ok] = channel.Recv();
        if (ok) {
            EXPECT_EQ(mat.getDX(), 2);
            EXPECT_EQ(mat.getDY(), 2);
            handled = true;
        }
        channel.Close();
    });

    Matrix mat(2, 2);
    channel.Send(mat);

    receiver.join();
    EXPECT_TRUE(handled);
}

TEST(BufferedChannelTest, MultipleProducersConsumers) {
    BufferedChannel<int> channel(100);
    std::atomic<int> counter{0};

    auto consumer = std::thread([&]() {
        while (true) {
            auto [val, ok] = channel.Recv();
            if (!ok) break;
            counter += val;
        }
    });

    std::vector<std::thread> producers;
    for (int i = 0; i < 10; ++i) {
        producers.emplace_back([&] {
            for (int j = 0; j < 100; ++j) {
                channel.Send(1);
            }
        });
    }

    for (auto& t : producers) t.join();
    channel.Close();
    consumer.join();

    EXPECT_EQ(counter.load(), 1000);
}

// === Тест на многопоточность === -- deprecated
/** 
TEST(ThreadTunnelTest, ThreadSafetyUnderParallelAccess) {
    ThreadTunnel<int> tunnel;
    std::atomic<int> counter{0};

    // Start the ThreadTunnel with a handler for incrementing the counter
    tunnel.start([&](int value) {
        counter += value;
    });

    // Launch multiple producer threads
    std::vector<std::thread> producers;
    for (int i = 0; i < 10; ++i) {
        producers.emplace_back([&]() {
            for (int j = 0; j < 100; ++j) {
                tunnel.send(1);
            }
        });
    }

    // Wait for all producers to finish
    for (auto& t : producers) {
        t.join();
    }

    // Stop the ThreadTunnel
    tunnel.stop();

    EXPECT_EQ(counter.load(), 1000);
}
    */