#include "PlayerMovementScene.h"
#include "Constants.h"
#include "InputMap.h"
#include "SceneSelectionScene.h"
#include <math.h>

#include <raylib.h>

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
    // Held actions: build a direction from the four axes. Diagonals fall out of this for free.
    Vector2 moveDirection{ 0.0f, 0.0f };
    float acceleration{ 25.0f };
    if (input.IsDown(Action::MOVE_UP))
    {
        moveDirection.y -= acceleration;
    }
    if (input.IsReleased(Action::MOVE_UP))
    {
        moveDirection.y = 0;
    }
    if (input.IsDown(Action::MOVE_DOWN))
    {
        moveDirection.y += acceleration;
    }
    if (input.IsReleased(Action::MOVE_DOWN))
    {
        moveDirection.y = 0;
    }
    if (input.IsDown(Action::MOVE_LEFT))
    {
        moveDirection.x -= acceleration;
    }
    if (input.IsReleased(Action::MOVE_LEFT))
    {
        moveDirection.x = 0;
    }
    if (input.IsDown(Action::MOVE_RIGHT))
    {
        moveDirection.x += acceleration;
    }
    if (input.IsReleased(Action::MOVE_RIGHT))
    {
        moveDirection.x = 0;
    }

    // Normalize so diagonals aren't faster than straight movement.
    float length{ std::sqrt(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y) };
    if (length > 0.0f)
    {
        moveDirection.x /= length;
        moveDirection.y /= length;
    }

    if (length > 0.0f)
    {
        direction = atan2f(moveDirection.y, moveDirection.x) * RAD2DEG;
    }

    velocity = {velocity.x + moveDirection.x, velocity.y + moveDirection.y};

}
void PlayerMovementScene::Update(float deltaTime)
{
    square.x += velocity.x * START_SPEED * deltaTime;
    square.y += velocity.y * START_SPEED * deltaTime;

    // Keep the square on screen.
    // square.x/y is the center (origin is SIZE/2), and the square is rotated,
    // so clamp using the half-extents of its rotated bounding box.
    float rad{ direction * DEG2RAD };
    float c{ std::fabs(std::cos(rad)) };
    float s{ std::fabs(std::sin(rad)) };
    float halfW{ (SIZE.x * c + SIZE.y * s) / 2.0f };
    float halfH{ (SIZE.x * s + SIZE.y * c) / 2.0f };

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
