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
