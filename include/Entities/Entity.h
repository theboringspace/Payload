#pragma once

#include <raylib.h>

/// Shared contract for anything in the tower-defense simulation that has a
/// position, ticks every frame, draws itself, and can become inactive
/// (an enemy dying, a turret being sold/destroyed, etc.). Combat-specific
/// state (health, range, damage...) stays on the derived classes.
class Entity
{
public:
    explicit Entity(Vector2 position_);

    virtual ~Entity() = default;

    /// Per-frame simulation step. Entities that need to see *other*
    /// entities (e.g. Turret targeting Enemies) do that via their own
    /// extra method, not through this signature.
    virtual void Update(float deltaTime) = 0;
    virtual void Draw()const = 0;

    Vector2 GetPosition()const;
    /// False once Deactivate() has been called.
    bool IsActive()const;

protected:
    void SetPosition(Vector2 position_);
    /// Marks the entity inactive (dead enemy, destroyed turret, ...). One-way.
    void Deactivate();

    Vector2 position;


private:
    bool active{ true };
};
