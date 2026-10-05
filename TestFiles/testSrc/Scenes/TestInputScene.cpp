#include "TestInputScene.h"
#include "Constants.h"
#include "SceneSelectionScene.h"

#include <cmath>
#include <raylib.h>

TestInputScene::TestInputScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_),
    backButton(10, 10, 300, 75, "Back to Selection", 30)
{
}

void TestInputScene::OnEnter()
{
    // Two keys on one action, to test the loop in IsDown()/IsPressed().
    input.Bind(Action::MOVE_UP,    KEY_W);
    input.Bind(Action::MOVE_UP,    KEY_UP);
    input.Bind(Action::MOVE_DOWN,  KEY_S);
    input.Bind(Action::MOVE_DOWN,  KEY_DOWN);
    input.Bind(Action::MOVE_LEFT,  KEY_A);
    input.Bind(Action::MOVE_LEFT,  KEY_LEFT);
    input.Bind(Action::MOVE_RIGHT, KEY_D);
    input.Bind(Action::MOVE_RIGHT, KEY_RIGHT);

    // Same key, different action. Which one is checked depends on the paused state.
    // Not ESC: raylib's default exit key would close the window.
    input.Bind(Action::PAUSE,   KEY_P);
    input.Bind(Action::UNPAUSE, KEY_P);

    input.Bind(Action::PLACE_TURRET, KEY_SPACE);
    input.Bind(Action::GACHA,        KEY_G);

    squarePosition = { (WINDOW_WIDTH - SQUARE_SIZE) / 2.0f, (WINDOW_HEIGHT - SQUARE_SIZE) / 2.0f };
}
void TestInputScene::OnExit()
{
}
void TestInputScene::OnPause()
{
}
void TestInputScene::OnResume()
{
}

void TestInputScene::HandleInput()
{
    if (backButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneSelectionScene>(events, manager));
        return;
    }

    // Pressed actions: only true for one frame, so they must be read here, not in Update().
    // else-if so PAUSE and UNPAUSE (both on P) can't flip back on the same frame.
    if (!paused && input.IsPressed(Action::PAUSE))
    {
        paused = true;
    }
    else if (paused && input.IsPressed(Action::UNPAUSE))
    {
        paused = false;
    }

    if (paused)
    {
        moveDirection = { 0.0f, 0.0f };
        return;
    }

    if (input.IsPressed(Action::PLACE_TURRET))
    {
        ++turretsPlaced;
    }
    if (input.IsPressed(Action::GACHA))
    {
        ++gachaPulls;
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

    moveDirection = direction;
}
void TestInputScene::Update(float deltaTime)
{
    squarePosition.x += moveDirection.x * SQUARE_SPEED * deltaTime;
    squarePosition.y += moveDirection.y * SQUARE_SPEED * deltaTime;

    // Keep the square on screen.
    if (squarePosition.x < 0.0f) squarePosition.x = 0.0f;
    if (squarePosition.y < 0.0f) squarePosition.y = 0.0f;
    if (squarePosition.x > WINDOW_WIDTH - SQUARE_SIZE)  squarePosition.x = WINDOW_WIDTH - SQUARE_SIZE;
    if (squarePosition.y > WINDOW_HEIGHT - SQUARE_SIZE) squarePosition.y = WINDOW_HEIGHT - SQUARE_SIZE;
}
void TestInputScene::Draw()
{
    ClearBackground(BLACK);

    DrawRectangleV(squarePosition, { SQUARE_SIZE, SQUARE_SIZE }, paused ? GRAY : SKYBLUE);

    int y{ 120 };
    DrawActionRow("MOVE_UP",      "W / Up",    Action::MOVE_UP,      y);
    DrawActionRow("MOVE_DOWN",    "S / Down",  Action::MOVE_DOWN,    y += 35);
    DrawActionRow("MOVE_LEFT",    "A / Left",  Action::MOVE_LEFT,    y += 35);
    DrawActionRow("MOVE_RIGHT",   "D / Right", Action::MOVE_RIGHT,   y += 35);
    DrawActionRow("PAUSE",        "P",         Action::PAUSE,        y += 35);
    DrawActionRow("UNPAUSE",      "P",         Action::UNPAUSE,      y += 35);
    DrawActionRow("PLACE_TURRET", "Space",     Action::PLACE_TURRET, y += 35);
    DrawActionRow("GACHA",        "G",         Action::GACHA,        y += 35);

    y += 60;
    DrawText(TextFormat("Turrets placed: %d", turretsPlaced), 10, y, 25, RAYWHITE);
    DrawText(TextFormat("Gacha pulls: %d", gachaPulls), 10, y += 35, 25, RAYWHITE);
    DrawText(TextFormat("Move direction: (%.2f, %.2f)", moveDirection.x, moveDirection.y), 10, y += 35, 25, RAYWHITE);

    if (paused)
    {
        DrawText("PAUSED - press P", (WINDOW_WIDTH - MeasureText("PAUSED - press P", 50)) / 2, 100, 50, YELLOW);
    }

    backButton.Draw();
}

void TestInputScene::DrawActionRow(const char* name, const char* keys, Action action, int y)const
{
    Color color{ input.IsDown(action) ? GREEN : DARKGRAY };

    DrawText(name, 10, y, 25, color);
    DrawText(keys, 220, y, 25, color);
}

bool TestInputScene::IsTransparent()const
{
    return false;
}
bool TestInputScene::BlocksUpdate()const
{
    return true;
}
std::string TestInputScene::GetName()const
{
    return "TestInputScene";
}
