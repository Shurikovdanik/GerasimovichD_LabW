#include "../include/BasicObject.h"
void BasicObject::addEventListener(Event *event)
{
    if (event->getID() >= this->events.size())
    {
        this->events.push_back(event);
    }
    else
    {
        this->events[event->getID()]->unite(event);
    }
}
void BasicObject::addEventListener(Event *event, EventListener *listener)
{
    event->addListener(listener);
    this->events.push_back(event);
}
void BasicObject::addEventListener(Event *event, EventHandler handler)
{
    EventListener *temp = new EventListener(handler);
    event->addListener(temp);
    this->events.push_back(event);
}
void BasicObject::addEventListeners(std::span<Event *> eventSpan)
{
    for (Event *e : eventSpan)
    {
        addEventListener(e);
    }
}

std::span<Event *> BasicObject::getEvents()
{
    return std::span<Event *>(events.data(), events.size());
}