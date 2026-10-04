#pragma once

#include <cstddef>
#include <typeindex>

class EventBus;

class EventSubscription
{
public:
    EventSubscription() = default;
    EventSubscription(EventBus* bus_, std::type_index type_, size_t id_);
    ~EventSubscription();

    EventSubscription(const EventSubscription&) = delete;
    EventSubscription& operator=(const EventSubscription&) = delete;

    EventSubscription(EventSubscription&& other) noexcept;
    EventSubscription& operator=(EventSubscription&& other) noexcept;

private:
    EventBus*       bus  { nullptr };
    std::type_index type { typeid(void) };
    size_t          id   { 0 };
};
