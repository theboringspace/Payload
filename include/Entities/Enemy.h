#pragma once

#include <raylib.h>
#include <vector>

#include "Entity.h"

/// Anything enemies should steer away from (turrets, the player, ...).
struct Threat
{
    Vector2 position;
    float   radius;     ///< Enemies start avoiding inside this distance.
};

/// Free-roaming enemy: flies toward a goal with momentum, steering away from
/// threats and other enemies. No fixed paths.
class Enemy : public Entity
{
public:
    Enemy(Vector2 position_, Vector2 goal_, float goalRadius_, float maxSpeed_, int maxHealth);

    /// Works out this frame's steering from threats and other enemies.
    /// Call it on every enemy before any enemy moves, so they all react
    /// to the same snapshot.
    void Steer(const std::vector<Threat>& threats, const std::vector<Enemy>& others);

    /// Applies steering to velocity, then velocity to position.
    void Update(float deltaTime) override;
    void Draw()const override;

    void TakeDamage(int amount);

    bool IsAlive()const;
    /// True if this enemy was deactivated by reaching the goal, not by dying.
    bool ReachedGoal()const;
    int GetHealth()const;

private:
    Vector2 goal;
    float goalRadius;
    Vector2 velocity{ 0.0f, 0.0f };
    Vector2 steering{ 0.0f, 0.0f };
    float maxSpeed;
    int health;
    bool reachedGoal{ false };

    static constexpr float SEEK_GAIN{ 4.0f };            // 1/s, how hard it turns toward the goal
    static constexpr float AVOID_ACCEL{ 8000.0f };       // px/s^2, push away from threats
    static constexpr float SIDESTEP_FACTOR{ 0.6f };      // Share of the avoid push used to slide around a threat
    static constexpr float SEPARATION_RADIUS{ 40.0f };   // px
    static constexpr float SEPARATION_ACCEL{ 1500.0f };  // px/s^2
    static constexpr float MAX_FORCE{ 6000.0f };         // px/s^2, caps how sharply it can turn
    static constexpr float RADIUS{ 15.0f };              // px, draw size
};
