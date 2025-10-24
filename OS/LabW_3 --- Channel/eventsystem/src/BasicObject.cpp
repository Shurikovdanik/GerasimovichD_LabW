#include "BasicObject.h"
void BasicObject::addEventListener(Event* event) {
    this->events.push_back(event);
}
void BasicObject::addEventListener(Event* event, EventListener* listener) {
    event->addListener(listener);
    this->events.push_back(event);
}
void BasicObject::addEventListener(Event* event, EventHandler handler) {
    EventListener* temp = new EventListener(handler);
    event->addListener(temp);
    this->events.push_back(event);
}