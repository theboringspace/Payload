#pragma once

#include <raylib.h>

// Every event type sent through EventBus. An event is just a plain struct.

/// An enemy was killed (not escaped).
struct EnemyDied
{
    Vector2 position;   ///< Where it died.
    int reward;
};
/// Enemies reached the goal.
struct EarthDamaged
{
    int amount;         ///< How many got through.
};
/// Not used yet.
struct WaveStarted
{
    int waveNumber;
};

// Test Events

// Time Adjustment Events
// FPS events are handled by the Sandbox's main loop, time scale events by GameClock.
struct IncreaseFPS
{
    int increase{ 0 };
};
struct DecreaseFPS
{
    int decrease{ 0 };
};
struct IncreaseTimeScale
{
    float increase{ 0 };
};
struct DecreaseTimeScale
{
    float decrease{ 0 };
};

/// Sent by GameClock whenever its time scale is set.
struct TimeScaleChanged
{
    float newTimeScale{ 1.0 };
};

struct ResetTimeScale
{
    float timeScale{ 1.0 };
};

// Frame Rate Events
struct ResetFPS
{
    int fps{ 60 };
};

// Player-caused Events
/// Game places a turret at the player's position.
struct SpawnTurret
{
};

// Projectiles
/// Game creates a Projectile from this.
struct ProjectileFired
{
    Vector2 startingPosition;
    Vector2 velocity;   ///< Pixels per second.
    float radius;       ///< Pixels.
};

/// Not used yet.
struct HitByProjectile
{
    float damage;
};
