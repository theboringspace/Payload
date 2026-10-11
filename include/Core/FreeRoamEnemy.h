#pragma once

#include <raylib.h>
#include <vector>

#include "Entity.h"

struct Threat
{
    Vector2 position;
    float   radius;
};

class FreeRoamEnemy : public Entity
{
public:
    FreeRoamEnemy(Vector2 position_, Vector2 goal_, float maxSpeed_, int maxHealth);

    /// Works out this frame's steering from threats and other enemies.
    /// Called for every enemy before any enemy moves, so they all react
    /// to the same snapshot.
    void Steer(const std::vector<Threat>& threats, const std::vector<FreeRoamEnemy>& others);

    /// Applies steering to velocity, then velocity to position.
    void Update(float deltaTime) override;

    void Draw()const override;

    void TakeDamage(int amount);

    bool IsAlive()const;

    bool ReachedGoal()const;

    int GetHealth()const;

private:
    Vector2 goal;

    Vector2 velocity{ 0.0f, 0.0f };
    Vector2 steering{ 0.0f, 0.0f };

    float maxSpeed;
    int health;
    bool reachedGoal { false };

    static constexpr float SEEK_GAIN{ 4.0f };               // 1/s
    static constexpr float AVOID_ACCEL{ 3000.0f };          // px/s^2
    static constexpr float SEPARATION_RADIUS{ 40.0f };      // px
    static constexpr float SEPARATION_ACCEL{ 1500.0f };     // px/s^2
    static constexpr float MAX_FORCE{ 3000.0f };            // px/s^2
    static constexpr float GOAL_RADIUS{ 30.0f };            // px
    static constexpr float RADIUS{ 15.0f };                 // px, draw size
};
