#pragma once
#include "Event.h"

namespace custom
{
    class ThreadFinEvent : public Event
    { // Нужно как-то размыслить над ID
    public:
        ThreadFinEvent() : Event(1) {}
    };
    class ThreadBeginEvent : public Event
    {
    public:
        ThreadBeginEvent() : Event(2) {}
    };
}