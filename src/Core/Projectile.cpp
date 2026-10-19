#include "Projectile.h"

Projectile::Projectile(Vector2 position_, Vector2 velocity_, float radius_)
:   Entity(position_), velocity(velocity_), radius(radius_)
{
}

void Projectile::Update(float deltaTime)
{
    if (!IsActive())
    {
        return;
    }

    if (outOfBounds || enemyHit)
    {
        Deactivate();
        return;
    }

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void Projectile::Draw() const
{
    if (!IsActive())
    {
        return;
    }

    DrawCircleV(position, radius, YELLOW);
}
