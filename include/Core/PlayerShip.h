#pragma once

/**
 * CLASS PlayerShip
 * --
 * The player's ship, with tank controls and momentum.
 *
 * MOVE_UP/MOVE_DOWN thrust forward/reverse along the facing, MOVE_LEFT/MOVE_RIGHT turn,
 * SLOW_DOWN brakes. Velocity carries over between frames, so the ship drifts until braked.
 *
 * Typical use:
 *      ship.HandleInput(input);       // every frame
 *      ship.Update(GameClock::FIXED_DT); // fixed step
 *      ship.Draw();
 */
#include <raylib.h>
#include "EventBus.h"
#include "Constants.h"
#include "InputMap.h"

class PlayerShip
{
public:
    /// size_ is the width and height of the ship, in pixels.
    explicit PlayerShip(float size_ = DEFAULT_SIZE);

    /**
     * FUNCTION HandleInput
     * --
     * Only reads what the player wants. Velocity is changed in Update(), at a fixed rate.
     */
    void HandleInput(const InputMap& input);
    /**
     * FUNCTION Update
     * --
     * Turn, thrust, brake, cap speed, move, then keep the ship on screen.
     */
    void Update(float deltaTime);
    /**
     * FUNCTION Draw
     * --
     * Draws the ship body with a nose marker showing its facing.
     */
    void Draw()const;

    /// Center of the ship.
    Vector2 GetPosition()const;
    Vector2 GetVelocity()const;
    /// How much braking removed on the last Update().
    Vector2 GetBrakingPower()const;
    /// Degrees, [0, 360). 0 faces right, 90 faces down.
    float   GetDirection()const;

private:
    Vector2 position{ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f };
    Vector2 velocity{ 0, 0 };
    // Read in HandleInput(), applied in Update()
    float thrustInput{ 0.0f }; // +1 forward, -1 reverse, 0 none
    float turnInput{ 0.0f };   // -1 left, +1 right, 0 none
    float direction{ 270.0f }; // Degrees, starts facing up
    Vector2 brakingPower{ 0, 0 }; // How much braking removed on the last Update(), for readouts
    bool braking{ false };
    float size;

    static constexpr float DEFAULT_SIZE{ 70.0f };
    static constexpr float ACCELERATION{ 60.0f };         // Velocity gained per second, forward thrust
    static constexpr float REVERSE_ACCELERATION{ 30.0f }; // Velocity gained per second, reverse thrust (weaker)
    static constexpr float TURN_SPEED{ 180.0f };          // Degrees per second
    static constexpr float BRAKE_STRENGTH{ 60.0f };       // Velocity lost per second while braking
    static constexpr float PIXELS{ 10.0f };               // Pixels moved per second per unit of velocity
    static constexpr float MAX_SPEED{ 100.0f };
};
