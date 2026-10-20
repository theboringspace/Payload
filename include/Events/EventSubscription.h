#pragma once

#include <cstddef>
#include <typeindex>

class EventBus;

/**
 * CLASS EventSubscription
 * --
 * Handle returned by EventBus::Subscribe(). Unsubscribes its handler when destroyed,
 * so a handler never outlives the object that owns this.
 *
 * Move-only. Moving it hands the subscription over; the moved-from one does nothing.
 * A default-constructed one isn't subscribed to anything.
 */
class EventSubscription
{
public:
    EventSubscription() = default;
    /// Made by EventBus::Subscribe(). Shouldn't need to be called directly.
    EventSubscription(EventBus* bus_, std::type_index type_, size_t id_);
    /// Unsubscribes, if still subscribed.
    ~EventSubscription();

    EventSubscription(const EventSubscription&) = delete;
    EventSubscription& operator=(const EventSubscription&) = delete;

    EventSubscription(EventSubscription&& other) noexcept;
    /// Unsubscribes whatever this was subscribed to before taking over other's.
    EventSubscription& operator=(EventSubscription&& other) noexcept;

private:
    EventBus*       bus  { nullptr };
    std::type_index type { typeid(void) };
    size_t          id   { 0 };
};
