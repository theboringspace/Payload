#pragma once
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <cstddef>
#include <utility>

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
        handlers[std::type_index(typeid(E))].push_back({ nextId, wrapper });
        ++nextId;
    }

    void Unsubscribe(std::type_index eventType, size_t eventId) ///< Remove Handler by ID
    {
        // Check if there are any subscribers to the event. If none, early return.
        auto found = handlers.find(eventType);
        if (found == handlers.end())
        {
            return;
        }

        auto& list = found->second;

        for (std::vector<EventHandler>::const_iterator eventHandler{ list.begin() }; eventHandler != list.end(); ++eventHandler)
        {
            if (eventHandler->id  == eventId)
            {
                list.erase(eventHandler);
                break;
            }
        }

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
        for (auto& entry : handlers[std::type_index(typeid(E))])
        {
            entry.function(&event);
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

        for (auto& deliver : queueLocal)
        {
            deliver();
        }
    }

private:
    using ErasedHandler = std::function<void(const void*)>;

    struct EventHandler
    {
        size_t id;
        ErasedHandler function;
    };

    std::unordered_map<std::type_index, std::vector<EventHandler>> handlers;
    std::vector<std::function<void()>> queue;

    size_t nextId{ 0 };
};
