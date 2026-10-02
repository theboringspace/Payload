#include "EventBus.h"
#include "Events.h"

struct PlayerDamaged { int health; };

class TestPlayer
{
public:
    TestPlayer(EventBus& events) : events_(events) {}

    void TakeDamage(int amount)
    {
        health_ -= amount;
        events_.Publish(PlayerDamaged{ health_ });   // "I got hit"
    }

private:
    EventBus& events_;
    int health_ = 100;
};
