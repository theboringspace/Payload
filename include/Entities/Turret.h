#pragma once

#include <raylib.h>
#include <vector>

#include "Entity.h"
#include "Enemy.h"

/// Stationary tower that hits the closest living enemy in range, then waits
/// out a cooldown. Shots are instant (no projectile); a line is drawn briefly to show them.
class Turret : public Entity
{
public:
    /// range_ is in pixels.
    explicit Turret(Vector2 position_, float range_ = DEFAULT_RANGE);

    /// Generic per-frame tick: just advances the fire cooldown. Does not
    /// know about Enemies -- see TryFire.
    void Update(float deltaTime) override;
    void Draw()const override;

    /// Combat-specific: scans enemies for a target in range and fires if
    /// off cooldown. Kept separate from Update() since it needs a list of
    /// Enemies, which Entity's per-frame signature doesn't carry.
    void TryFire(std::vector<Enemy>& enemies);

    float GetRange()const;

    static constexpr float DEFAULT_RANGE{ 400.0f };

private:
    float range;     ///< Pixels.
    float fireRate;  ///< Seconds between shots.
    float fireTimer; ///< Seconds until it can fire again.
    int damage;      ///< Damage per shot.

    Vector2 shotTarget{ 0.0f, 0.0f }; ///< Where the last shot landed.
    float shotTimer{ 0.0f };          ///< Time left to show the last shot.

    static constexpr float SHOT_DURATION{ 0.1f };
};
