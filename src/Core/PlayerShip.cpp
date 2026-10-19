#include "PlayerShip.h"
#include "Events.h"

#include <cmath>
#include <raymath.h>

PlayerShip::PlayerShip(EventBus& events_, float size_)
:   events(events_), size(size_)
{
}

void PlayerShip::HandleInput(const InputMap& input)
{
    /**
     * MOVEMENT
     */
    // Holding both keys of a pair cancels out to 0.
    thrustInput = 0.0f;
    if (input.IsDown(Action::MOVE_UP))   thrustInput += 1.0f;
    if (input.IsDown(Action::MOVE_DOWN)) thrustInput -= 1.0f;

    turnInput = 0.0f;
    if (input.IsDown(Action::MOVE_LEFT))  turnInput -= 1.0f;
    if (input.IsDown(Action::MOVE_RIGHT)) turnInput += 1.0f;

    // "Is it held right now?" every frame, so it can't get stuck on.
    braking = input.IsDown(Action::SLOW_DOWN);

    /**
     * ATTACKS
     */
    if (input.IsPressed(Action::PLACE_TURRET)) events.Enqueue(SpawnTurret{});
    if (input.IsPressed(Action::FIRE_PROJECTILE)) events.Enqueue(ProjectileFired{position, {100 * 20 * cos(direction * DEG2RAD), 100 * 20 * sin(direction * DEG2RAD)}, 10});


}

void PlayerShip::Update(float deltaTime)
{
    // 1. Turn. Screen y points down, so a bigger angle turns clockwise (right).
    direction += turnInput * TURN_SPEED * deltaTime;
    // Keep it in [0, 360) so it doesn't grow forever.
    direction = std::fmod(direction, 360.0f);
    if (direction < 0.0f)
    {
        direction += 360.0f;
    }

    // Thrust along the facing. Reverse is weaker than forward.
    if (thrustInput != 0.0f)
    {
        float rad{ direction * DEG2RAD };
        Vector2 forward{ std::cos(rad), std::sin(rad) };
        float thrust{ thrustInput > 0.0f ? ACCELERATION : -REVERSE_ACCELERATION };

        velocity.x += forward.x * thrust * deltaTime;
        velocity.y += forward.y * thrust * deltaTime;
    }

    // 2. Brake: slow down along the direction of travel, never past zero.
    brakingPower = { 0.0f, 0.0f };
    float speed{ std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y) };
    if (braking && speed > 0.0f)
    {
        float brakeAmount{ BRAKE_STRENGTH * deltaTime };
        if (brakeAmount >= speed)
        {
            // Close enough: stop completely, both axes at once.
            brakingPower = velocity;
            velocity = { 0.0f, 0.0f };
        }
        else
        {
            // velocity / speed is the direction of travel, length 1.
            brakingPower = { velocity.x / speed * brakeAmount, velocity.y / speed * brakeAmount };
            velocity.x -= brakingPower.x;
            velocity.y -= brakingPower.y;
        }
    }

    // 3. Speed cap.
    speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed > MAX_SPEED)
    {
        velocity.x = (velocity.x / speed) * MAX_SPEED;
        velocity.y = (velocity.y / speed) * MAX_SPEED;
    }

    // 4. Move.
    position.x += velocity.x * PIXELS * deltaTime;
    position.y += velocity.y * PIXELS * deltaTime;

    // Keep the ship on screen. position is the center, so stop half a size from each edge.
    float halfW{ size / 2.0f };
    float halfH{ size / 2.0f };

    if (position.x < halfW)
    {
        position.x = halfW;
        velocity.x = 0.0f;
    }
    if (position.x > WINDOW_WIDTH - halfW)
    {
        position.x = WINDOW_WIDTH - halfW;
        velocity.x = 0.0f;
    }
    if (position.y < halfH)
    {
        position.y = halfH;
        velocity.y = 0.0f;
    }
    if (position.y > WINDOW_HEIGHT - halfH)
    {
        position.y = WINDOW_HEIGHT - halfH;
        velocity.y = 0.0f;
    }
}

void PlayerShip::Draw()const
{
    // DrawRectanglePro rotates around origin, so x/y here is the center.
    Rectangle body{ position.x, position.y, size, size };
    Vector2 origin{ size / 2.0f, size / 2.0f };
    DrawRectanglePro(body, origin, direction, WHITE);

    // Nose marker, so the facing is visible.
    float rad{ direction * DEG2RAD };
    Vector2 tip{ position.x + std::cos(rad) * size / 2.0f,
                 position.y + std::sin(rad) * size / 2.0f };

    DrawCircleV(tip, size * 0.1f, SKYBLUE);
    DrawLineEx(position, tip, size * 0.05f, SKYBLUE);
}

Vector2 PlayerShip::GetPosition()const
{
    return position;
}

Vector2 PlayerShip::GetVelocity()const
{
    return velocity;
}

Vector2 PlayerShip::GetBrakingPower()const
{
    return brakingPower;
}

float PlayerShip::GetDirection()const
{
    return direction;
}
