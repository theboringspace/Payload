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
    Vector2 direction{ 0.0f, 0.0f };
    if (input.IsDown(Action::MOVE_UP))    direction.y -= 100.0f;
    if (input.IsDown(Action::MOVE_DOWN))  direction.y += 100.0f;
    if (input.IsDown(Action::MOVE_LEFT))  direction.x -= 100.0f;
    if (input.IsDown(Action::MOVE_RIGHT)) direction.x += 100.0f;

    // Normalize so diagonals aren't faster than straight movement.
    float length{ std::sqrt(direction.x * direction.x + direction.y * direction.y) };
    if (length > 0.0f)
    {
        direction.x /= length;
        direction.y /= length;
    }

    velocity = direction;

}
void PlayerMovementScene::Update(float deltaTime)
{
    position.x += velocity.x * SPEED * deltaTime;
    position.y += velocity.y * SPEED * deltaTime;

    // Keep the square on screen.
    if (position.x < 0.0f) position.x = 0.0f;
    if (position.y < 0.0f) position.y = 0.0f;
    if (position.x > WINDOW_WIDTH  - SIZE.x)  position.x = WINDOW_WIDTH  - SIZE.x;
    if (position.y > WINDOW_HEIGHT - SIZE.y)  position.y  = WINDOW_HEIGHT - SIZE.y;
}
void PlayerMovementScene::Draw()
{
    ClearBackground(BLACK);

    backButton.Draw();

    DrawRectangleV(position, SIZE, WHITE);
    DrawCircleV(Vector2{ position.x + SIZE.x, position.y + SIZE.y / 2 }, 7.5, SKYBLUE);
    DrawLineEx(Vector2{ position.x + SIZE.x / 2, position.y + SIZE.y / 2 }, Vector2{ position.x + SIZE.x, position.y + SIZE.y / 2 }, 3.5, SKYBLUE);


}

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
