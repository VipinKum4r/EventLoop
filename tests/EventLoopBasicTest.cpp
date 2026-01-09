#include <gtest/gtest.h>
#include <EventLoop.h>
#include <atomic>
#include <Event.h>

TEST(EventLoopBasicTest, BasicEventLoopFlow)
{
    std::atomic<bool> handlerCalled{false};
    int value = 42;

    EventLoop::RegisterEvent("TestEvent", [&](EventLoop::Event*) {
        handlerCalled = true;
    });

    EventLoop::RegisterEvent("DataEvent", [&](EventLoop::Event* evt) {
        int* data = static_cast<int*>(evt->getData());
        EXPECT_EQ(*data, 42);
        EventLoop::Halt();
    });

    EventLoop::TriggerEvent("TestEvent");
    EventLoop::TriggerEvent("DataEvent", &value);

    EventLoop::Run();

    EXPECT_TRUE(handlerCalled.load());
}
