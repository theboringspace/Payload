#include "EventSubscription.h"
#include "EventBus.h"

EventSubscription::EventSubscription(EventBus* bus_, std::type_index type_, size_t id_)
:   bus(bus_), type(type_), id(id_)
{
}
EventSubscription::~EventSubscription()
{
    if (bus)
    {
        bus->Unsubscribe(type, id);
    }
}

EventSubscription::EventSubscription(EventSubscription&& other) noexcept
{
    bus  = other.bus;
    type = other.type;
    id   = other.id;

    other.bus = nullptr;
}
EventSubscription& EventSubscription::operator=(EventSubscription&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    if (bus != nullptr)
    {
        bus->Unsubscribe(type, id);
    }

    bus  = other.bus;
    type = other.type;
    id   = other.id;

    other.bus = nullptr;

    return *this;
}
