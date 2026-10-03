#pragma once

#include <raylib.h>

struct EnemyDied
{
    Vector2 position;
    int reward;
};
struct EarthDamaged
{
    int amount;
};
struct WaveStarted
{
    int waveNumber;
};

// Test Events

// Time Adjustment Events
struct IncreaseFPS
{
    int increase{};
};
struct DecreaseFPS
{
    int decrease{};
};
struct IncreaseTimeScale
{
    float increase{};
};
struct DecreaseTimeScale
{
    float decrease{};
};

struct TimeScaleChanged
{
    float newTimeScale;
};
