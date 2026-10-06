#include "PlayerMovementScene.h"
#include "Constants.h"
#include "InputMap.h"
#include "SceneSelectionScene.h"

#include <raylib.h>
#include <cmath>

PlayerMovementScene::PlayerMovementScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_),
    backButton(10, 10, 300, 75, "Back to Selection", 30)
{
}

void PlayerMovementScene::OnEnter()
{
    input.Bind(Action::MOVE_UP, KEY_W);
    input.Bind(Action::MOVE_DOWN, KEY_S);
    input.Bind(Action::MOVE_LEFT, KEY_A);
    input.Bind(Action::MOVE_RIGHT, KEY_D);
    input.Bind(Action::SLOW_DOWN, KEY_SPACE);

}
void PlayerMovementScene::OnExit()
{
    input.Clear();
}
void PlayerMovementScene::OnPause()
{
}
void PlayerMovementScene::OnResume()
{
}

void PlayerMovementScene::HandleInput()
{
    if (backButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneSelectionScene>(events, manager));
    }
    // Only read what the player wants here. Velocity is changed in Update(), at a fixed rate.
    // Tank controls: MOVE_UP/DOWN are forward/reverse thrust, MOVE_LEFT/RIGHT turn.
    // Holding both keys of a pair cancels out to 0.
    thrustInput = 0.0f;
    if (input.IsDown(Action::MOVE_UP))   thrustInput += 1.0f;
    if (input.IsDown(Action::MOVE_DOWN)) thrustInput -= 1.0f;

    turnInput = 0.0f;
    if (input.IsDown(Action::MOVE_LEFT))  turnInput -= 1.0f;
    if (input.IsDown(Action::MOVE_RIGHT)) turnInput += 1.0f;

    // "Is it held right now?" every frame, so it can't get stuck on.
    braking = input.IsDown(Action::SLOW_DOWN);
}
void PlayerMovementScene::Update(float deltaTime)
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
    square.x += velocity.x * PIXELS * deltaTime;
    square.y += velocity.y * PIXELS * deltaTime;


    // Keep the square on screen. square.x/y is the center, so stop half a size from each edge.
    float halfW{ SIZE.x / 2.0f };
    float halfH{ SIZE.y / 2.0f };

    if (square.x < halfW)
    {
        square.x = halfW;
        velocity.x = 0.0f;
    }
    if (square.x > WINDOW_WIDTH - halfW)
    {
        square.x = WINDOW_WIDTH - halfW;
        velocity.x = 0.0f;
    }
    if (square.y < halfH)
    {
        square.y = halfH;
        velocity.y = 0.0f;
    }
    if (square.y > WINDOW_HEIGHT - halfH)
    {
        square.y = WINDOW_HEIGHT - halfH;
        velocity.y = 0.0f;
    }
}

void PlayerMovementScene::Draw()
{
    ClearBackground(BLACK);

    backButton.Draw();


    DrawRectanglePro(square,
                     origin,
                     direction,
                     WHITE);

    float rad = direction * DEG2RAD;
    Vector2 tip{ square.x + std::cos(rad) * SIZE.x / 2,
                 square.y + std::sin(rad) * SIZE.y / 2 };

    DrawCircleV(tip,
                7.5,
                SKYBLUE);
    DrawLineEx(Vector2{ square.x, square.y },
               tip,
               3.5,
               SKYBLUE);

    // Position, velocity, and braking readout, under the back button in the top left corner.
    DrawText(TextFormat("Position X: %.1f", square.x),       10, 95,  25, RAYWHITE);
    DrawText(TextFormat("Position Y: %.1f", square.y),       10, 130, 25, RAYWHITE);
    DrawText(TextFormat("Velocity X: %.2f", velocity.x),     10, 165, 25, RAYWHITE);
    DrawText(TextFormat("Velocity Y: %.2f", velocity.y),     10, 200, 25, RAYWHITE);
    DrawText(TextFormat("Braking X: %.2f", brakingPower.x),  10, 235, 25, RAYWHITE);
    DrawText(TextFormat("Braking Y: %.2f", brakingPower.y),  10, 270, 25, RAYWHITE);
};

bool PlayerMovementScene::IsTransparent()const
{
    return false;
}
bool PlayerMovementScene::BlocksUpdate()const
{
    return true;
}
std::string PlayerMovementScene::GetName()const
{
    return "PlayerMovementScene";
}
