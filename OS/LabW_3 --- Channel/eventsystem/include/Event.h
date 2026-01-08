#pragma once
#include <vector>
#include "EventListener.h"
/**
 * Класс наблюдаемый, вызываемый -- простое событие без дополнительных параметров
 */
class Event
{
private:
    int id;
    std::vector<EventListener *> _listeners;

public:
    /**
     * Объединяет вектора слушателей под одним событием, если их идентификаторы равны, иначе не меняет.
     */
    Event(int id)
    {
        this->id = id;
    }
    void unite(Event *other);
    int getID()
    {
        return id;
    }
    Event() = default;
    virtual void emit()
    {
        for (EventListener *cur : _listeners)
        {
            cur->update();
        }
    }
    /** Adds Listener to Event
     * @note
     * It is strongly recommended NOT to call Event->addListener(listener) manually.
     */
    void addListener(EventListener *listener)
    {
        this->_listeners.push_back(listener);
    }
};