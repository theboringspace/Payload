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
