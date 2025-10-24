#pragma once
#include <vector>
#include "EventListener.h"
/**
 * Класс наблюдаемый, вызываемый -- простое событие без дополнительных параметров
 */
class Event {
    private:
    std::vector<EventListener*> _listeners;
    public:
    Event() = default;
    virtual void emit() {
        for (EventListener* cur : _listeners) {
            cur->update();
        }
    }
    /** Adds Listener to Event
     * @note
     * It is strongly recommended NOT to call Event->addListener(listener) manually.
     */
    void addListener(EventListener* listener) {
        this->_listeners.push_back(listener);
    }

};