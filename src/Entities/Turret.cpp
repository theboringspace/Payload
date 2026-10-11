#include "Turret.h"

#include <raymath.h>

Turret::Turret(Vector2 position_, float range_)
:   Entity(position_),
    range(range_),
    fireRate(0.1f),
    fireTimer(0.0f),
    damage(1)
{
}

void Turret::Update(float deltaTime)
{
    if (fireTimer > 0) fireTimer -= deltaTime;
    if (shotTimer > 0) shotTimer -= deltaTime;
}

void Turret::Draw()const
{
    DrawCircleLines(static_cast<int>(GetPosition().x), static_cast<int>(GetPosition().y), range, LIGHTGRAY);
    DrawCircleV(GetPosition(), 20.0f, BLUE);

    if (shotTimer > 0) DrawLineV(GetPosition(), shotTarget, YELLOW);
}

void Turret::TryFire(std::vector<Enemy>& enemies)
{
    if (fireTimer > 0.0f) return;

    // Shoot the closest living enemy in range.
    Enemy* target{ nullptr };
    float closest{ range };
    for (auto& enemy : enemies)
    {
        if (!enemy.IsAlive()) continue;

        float distance{ Vector2Distance(GetPosition(), enemy.GetPosition()) };
        if (distance <= closest)
        {
            closest = distance;
            target = &enemy;
        }
    }

    if (target == nullptr) return;

    target->TakeDamage(damage);

    // Remembered here, drawn in Draw().
    shotTarget = target->GetPosition();
    shotTimer = SHOT_DURATION;

    fireTimer = fireRate;
}

float Turret::GetRange()const
{
    return range;
}
