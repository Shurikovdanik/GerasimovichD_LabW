#pragma once
#include <functional>
#include <thread>
#include "BasicObject.h"
#include "Event.h"
#include "ThreadEvent.h"
namespace custom
{
    class Thread : public BasicObject
    {
        std::thread worker;

    public:
        template <typename Callable, typename... Args>
        Thread(Callable &&func, Args &&...args)
        {
            ThreadFinEvent *fin = new ThreadFinEvent();
            auto boundFunc = std::bind(std::forward<Callable>(func), std::forward<Args>(args)...);

            std::function<void(void)> methodExtended = [=]()
            {
                boundFunc();
                fin->emit();
            };

            this->addEventListener(new ThreadBeginEvent(), methodExtended);
        }

        void start()
        {
            worker = std::thread([this]()
                                 { emitById(2); });
        }

        void join()
        {
            if (worker.joinable())
                worker.join();
        }
    };

}