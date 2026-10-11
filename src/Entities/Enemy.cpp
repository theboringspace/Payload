#include "Enemy.h"

#include <algorithm>

#include <raylib.h>
#include <raymath.h>

#include "Constants.h"

namespace
{
    /// Push away from a point, scaled 0..1 by how deep inside the radius we are.
    Vector2 PushAway(Vector2 self, Vector2 from, float radius, float accel)
    {
        Vector2 away{ Vector2Subtract(self, from) };
        float distance{ Vector2Length(away) };
        if (distance <= 0.0f || distance >= radius) return { 0.0f, 0.0f };

        float strength{ (radius - distance) / radius };
        return Vector2Scale(away, strength * accel / distance);
    }
}

Enemy::Enemy(Vector2 position_, Vector2 goal_, float goalRadius_, float maxSpeed_, int maxHealth)
:   Entity(position_),
    goal(goal_),
    goalRadius(goalRadius_),
    maxSpeed(maxSpeed_),
    health(maxHealth)
{
}

void Enemy::Steer(const std::vector<Threat>& threats, const std::vector<Enemy>& others)
{
    // Seek: steer toward full speed in the goal's direction.
    Vector2 toGoal{ Vector2Normalize(Vector2Subtract(goal, GetPosition())) };
    Vector2 desired{ Vector2Scale(toGoal, maxSpeed) };
    Vector2 force{ Vector2Scale(Vector2Subtract(desired, velocity), SEEK_GAIN) };

    // Avoid turrets and the player.
    for (const Threat& threat : threats)
    {
        Vector2 push{ PushAway(GetPosition(), threat.position, threat.radius, AVOID_ACCEL) };
        force = Vector2Add(force, push);

        // Sidestep: if a threat sits right between us and the goal, seek and avoid cancel out
        // and the enemy hovers. Also push sideways, toward the goal's side, so it slides around.
        Vector2 sideways{ -push.y, push.x };
        if (Vector2DotProduct(sideways, toGoal) < 0.0f)
        {
            sideways = Vector2Negate(sideways);
        }
        force = Vector2Add(force, Vector2Scale(sideways, SIDESTEP_FACTOR));
    }

    // Separation: don't stack on top of other enemies.
    for (const Enemy& other : others)
    {
        if (&other == this || !other.IsAlive()) continue;
        force = Vector2Add(force, PushAway(GetPosition(), other.GetPosition(), SEPARATION_RADIUS, SEPARATION_ACCEL));
    }

    steering = Vector2ClampValue(force, 0.0f, MAX_FORCE);
}

void Enemy::Update(float deltaTime)
{
    if (!IsAlive()) return;

    velocity = Vector2Add(velocity, Vector2Scale(steering, deltaTime));
    velocity = Vector2ClampValue(velocity, 0.0f, maxSpeed);

    // Threats can push enemies sideways hard, so keep them on screen.
    Vector2 next{ Vector2Add(GetPosition(), Vector2Scale(velocity, deltaTime)) };
    next.x = std::clamp(next.x, 0.0f, static_cast<float>(WINDOW_WIDTH));
    next.y = std::clamp(next.y, RADIUS, WINDOW_HEIGHT - RADIUS);
    SetPosition(next);

    // Touching the goal counts as reaching it.
    if (Vector2Distance(GetPosition(), goal) <= goalRadius + RADIUS)
    {
        reachedGoal = true;
        Deactivate();
    }
}

void Enemy::Draw()const
{
    if (IsAlive())
    {
        DrawCircleV(GetPosition(), RADIUS, RED);
    }
}

void Enemy::TakeDamage(int amount)
{
    health -= amount;
    if (health <= 0)
    {
        Deactivate();
    }
}

bool Enemy::IsAlive()const
{
    return IsActive();
}

bool Enemy::ReachedGoal()const
{
    return reachedGoal;
}

int Enemy::GetHealth()const
{
    return health;
}
