#pragma once
#include <raylib.h>
#include "Events.h"
#include "EventSubscription.h"

#include "Entity.h"

/**
 * CLASS Projectile
 * --
 * A circle that flies in a straight line at a constant velocity.
 * Created by Game when a ProjectileFired event comes in.
 *
 * Deactivates itself once outOfBounds or enemyHit is set
 * (nothing sets them yet, so for now it flies forever).
 */
class Projectile : public Entity
{
public:
    /// velocity_ is in pixels per second, radius_ is in pixels.
    Projectile(Vector2 position_, Vector2 velocity_, float radius_);

    /// Moves the projectile, or deactivates it if it's out of bounds or hit an enemy.
    virtual void Update(float deltaTime) override;
    /// Yellow circle. Draws nothing once inactive.
    virtual void Draw()const override;

private:
    // Raw Intrinsics
    const int PIXELS_PER{ 100 }; // Unused for now
    Vector2 velocity;            // Pixels per second
    float radius;                // Pixels

    bool outOfBounds{ false };
    bool enemyHit{ false };
};
