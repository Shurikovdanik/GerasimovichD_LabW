#pragma once
#include <vector>
#include <span>
#include <map>
#include <functional>
#include "Event.h"
#include "EventListener.h"
class BasicObject
{
private:
    std::vector<Event *> events;

protected:
    void emitById(int id)
    {
        for (auto &cur : events)
        {
            if (cur->getID() == id)
            {
                cur->emit();
                return;
            }
        }
    }

public:
    /**Adds listener to object called by event
     * @param event -- event, that causes activation
     * @param listener -- object of EventListener
     * @param handler -- func void(void)
     * @note override with no second parameter is strongly recommended NOT to use
     */
    void addEventListener(Event *);
    void addEventListener(Event *, EventListener *);
    void addEventListener(Event *, EventHandler);
    void addEventListeners(std::span<Event *> eventSpan);
    std::span<Event *> getEvents();
};