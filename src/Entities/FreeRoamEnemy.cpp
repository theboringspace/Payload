#include "FreeRoamEnemy.h"

#include "raymath.h"

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

FreeRoamEnemy::FreeRoamEnemy(Vector2 position_, Vector2 goal_, float maxSpeed_, int maxHealth)
:   Entity(position_), goal(goal_), maxSpeed(maxSpeed_), health(maxHealth)
{
}

void FreeRoamEnemy::Steer(const std::vector<Threat>& threats, const std::vector<FreeRoamEnemy>& others)
{
    // Seek: steer toward full speed in the goal's direction.
    Vector2 toGoal{ Vector2Normalize(Vector2Subtract(goal, GetPosition())) };
    Vector2 desired{ Vector2Scale(toGoal, maxSpeed) };
    Vector2 force{ Vector2Scale(Vector2Subtract(desired, velocity), SEEK_GAIN) };

    // Avoid turrets and the player.
    for (const Threat& threat : threats)
    {
        force = Vector2Add(force, PushAway(GetPosition(), threat.position, threat.radius, AVOID_ACCEL));
    }

    // Separation: don't stack on top of other enemies.
    for (const FreeRoamEnemy& other : others)
    {
        if (&other == this || !other.IsAlive()) continue;

        force = Vector2Add(force, PushAway(GetPosition(), other.GetPosition(), SEPARATION_RADIUS, SEPARATION_ACCEL));
    }

    // Stirrrr
    steering = Vector2ClampValue(force, 0.0f, MAX_FORCE);
}

void FreeRoamEnemy::Update(float deltaTime)
{
    if (!IsAlive()) { return; };

    velocity = Vector2Add(velocity, Vector2Scale(steering, deltaTime));
    velocity = Vector2ClampValue(velocity, 0.0f, maxSpeed);
    SetPosition(Vector2Add(GetPosition(), Vector2Scale(velocity, deltaTime)));

    if (Vector2Distance(GetPosition(), goal) <= GOAL_RADIUS)
    {
        reachedGoal = true;
        Deactivate();
    }
}

void FreeRoamEnemy::Draw()const
{
    if (IsAlive())
    {
        DrawCircleV(GetPosition(), 15.0f, RED);
    }
}

void FreeRoamEnemy::TakeDamage(int amount)
{
    health -= amount;
    if (health <= 0)
    {
        Deactivate();
    }
}

bool FreeRoamEnemy::IsAlive()const
{
    return IsActive();
}
bool FreeRoamEnemy::ReachedGoal()const
{
    return Vector2Equals(position, goal) ;
}

int FreeRoamEnemy::GetHealth()const
{
    return health;
}
