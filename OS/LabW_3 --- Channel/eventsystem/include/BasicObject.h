#pragma once
#include <vector>
#include <functional>
#include "Event.h"
#include "EventListener.h"
class BasicObject {
private:
std::vector<Event*> events;
public:
/**Adds listener to object called by event
 * @param event -- event, that causes activation
 * @param listener -- object of EventListener
 * @param handler -- func void(void)
 * @note override with no second parameter is strongly recommended NOT to use
 */
void addEventListener(Event*);
void addEventListener(Event*, EventListener*);
void addEventListener(Event*, EventHandler);
};