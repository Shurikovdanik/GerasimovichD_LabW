#pragma once
#include <functional>
using EventHandler = std::function<void(void)>;
/**
 * Наблюдатель, наблюдает за Event
 */
class EventListener {
    private:
    EventHandler handler;

    public:

    EventListener(EventHandler handler);
    /**
     * активация слушатель
     * @note
     * вызов через update крайне нежедателен
     */
    void update();
};