#pragma once

#include <raylib.h>
#include <vector>
#include <functional>

struct EnemyDied
{
    Vector2 position;
    int reward;
};

class EnemyDiedBus {
public:
    void Subscribe(std::function<void(const EnemyDied&)> handler)
    {
        handlers_.push_back(handler);       // remember this listener
    }

    void Publish(const EnemyDied& event)
    {
        for (auto& handler : handlers_)     // call every listener
            handler(event);
    }

private:
    std::vector<std::function<void(const EnemyDied&)>> handlers_;
};
