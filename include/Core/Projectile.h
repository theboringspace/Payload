#pragma once
#include <raylib.h>
#include "Events.h"
#include "EventSubscription.h"

#include "Entity.h"

class Projectile : public Entity
{
public:
    Projectile(Vector2 position_, Vector2 velocity_, float radius_);

    virtual void Update(float deltaTime) override;
    virtual void Draw()const override;

private:
    // Raw Intrinsics
    const int PIXELS_PER{ 100 };
    Vector2 velocity;
    float radius;

    bool outOfBounds{ false };
    bool enemyHit{ false };
};
