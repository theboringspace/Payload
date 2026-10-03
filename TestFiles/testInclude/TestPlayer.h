#pragma once

#include "EventBus.h"
#include "Events.h"

struct PlayerDamaged { int health; };
struct PlayerKills   { int kills; };

class TestPlayer
{
public:
    TestPlayer(EventBus& events) : events_(events) {}

    void TakeDamage(int amount)
    {
        health_ -= amount;
        events_.Enqueue(PlayerDamaged{ health_ });   // "I got hit"
    }
    void Kill()
    {
        ++kills;
        events_.Enqueue(PlayerKills{ kills });
    }

private:
    EventBus& events_;
    int health_ = 100;
    int kills   = 0;
};
