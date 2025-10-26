#include "Event.h"
void Event::unite(Event *other)
{
    if (this->id == other->getID())
    {
        for (auto &cur : other->_listeners)
        {
            this->_listeners.push_back(cur);
        }
    }
}