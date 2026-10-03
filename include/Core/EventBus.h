#pragma once
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

/// Centralized, type-based Subscribe/Publish Event Bus with queued dispatch.
class EventBus
{
public:
    template <typename E>
    void Subscribe(std::function<void(const E&)> handler) ///< Add to the Map
    {
        // Build a function that will run LATER, when E is published.
        ErasedHandler wrapper = [handler](const void* event)
            {
                const E* typed = static_cast<const E*>(event);
                handler(*typed);
            };

        // Store the built function into E's list to be published later.
        handlers[std::type_index(typeid(E))].push_back(wrapper);
    }
    template <typename E>
    void Publish(const E& event) ///<n Call every handler subscribed to event type E
    {
        // Look up E's list.
        auto it = handlers.find(std::type_index(typeid(E)));

        if (it == handlers.end()) // No Subscribers, do nothing.
        {
            return;
        }

        // Call every wrapper with the event's address
        // Each wrapper casts it back to E and calls its handler.
        // The list is only read here; subs stay for future events.
        for (auto& handler : handlers[std::type_index(typeid(E))])
        {
            handler(&event);
        }
    }

    template <typename E>
    void Enqueue(E event)
    {
        queue.push_back([this, event](){ Publish(event); });
    }

    void Dispatch()
    {
        std::vector<std::function<void()>> queueLocal{ std::move(queue) };
        queue.clear();

        for (auto& event : queueLocal)
        {
            event();
        }
    }

private:
    using ErasedHandler = std::function<void(const void*)>;
    std::unordered_map<std::type_index, std::vector<ErasedHandler>> handlers;

    std::vector<std::function<void()>> queue;
};
