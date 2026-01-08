#include "../include/EventListener.h"

EventListener::EventListener(EventHandler handler)
{
    this->handler = handler;
}
void EventListener::update()
{
    handler();
}