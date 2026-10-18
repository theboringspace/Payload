#include "EntitySimulationScene.h"
#include "SceneSelectionScene.h"

#include "Constants.h"
#include "Events.h"

#include <raylib.h>
#include <algorithm>

EntitySimulationScene::EntitySimulationScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_),
    backButton(10, 10, 300, 75, "Back to Selection", 30),
    game(events_)
{
    camera.target = { 100, 100 };
    camera.zoom = 1.5f;
    camera.offset = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f };
    camera.rotation = 0;


    // Subscriptions
    earthDamagedSubscription = events.Subscribe<EarthDamaged>([this](const EarthDamaged& event)
        {
            breached += event.amount;
        });
    enemyDiedSubscription = events.Subscribe<EnemyDied>([this](const EnemyDied&)
        {
            ++killed;
        });
}

void EntitySimulationScene::OnEnter()
{
    input.Bind(Action::MOVE_UP, KEY_W);
    input.Bind(Action::MOVE_DOWN, KEY_S);
    input.Bind(Action::MOVE_LEFT, KEY_A);
    input.Bind(Action::MOVE_RIGHT, KEY_D);
    input.Bind(Action::SLOW_DOWN, KEY_SPACE);
    input.Bind(Action::PLACE_TURRET, KEY_T);
}

void EntitySimulationScene::OnExit()
{
    input.Clear();
}

void EntitySimulationScene::HandleInput()
{
    if (backButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneSelectionScene>(events, manager));
    }

    game.HandleInput(input);
}

void EntitySimulationScene::Update(float deltaTime)
{
    game.Update(deltaTime);
    camera.target = game.GetPlayer().GetPosition();

    // Game doesn't know about the EventBus, so turn what happened into events here.
    GameResults results{ game.TakeResults() };
    if (results.escaped > 0)
    {
        events.Enqueue(EarthDamaged{ results.escaped });
    }
    for (const Vector2& position : results.killed)
    {
        events.Enqueue(EnemyDied{ position, KILL_REWARD });
    }
}

void EntitySimulationScene::Draw()
{
    ClearBackground(BLACK);

    BeginMode2D(camera);
    game.Draw();
    EndMode2D();

    // Breached count above the goal, kept on screen since the goal hugs the right edge.
    constexpr int FONT_SIZE{ 30 };
    const char* breachedText{ TextFormat("Breached Enemies: %d", breached) };
    int textWidth{ MeasureText(breachedText, FONT_SIZE) };
    Vector2 goal{ game.GetGoal() };
    int textX{ std::min(static_cast<int>(goal.x) - textWidth / 2, WINDOW_WIDTH - textWidth - 10) };
    int textY{ static_cast<int>(goal.y - Game::GOAL_RADIUS) - FONT_SIZE - 15 };
    DrawText(breachedText, textX, textY, FONT_SIZE, RAYWHITE);

    DrawText(TextFormat("Killed: %d", killed), 10, 95, 25, RAYWHITE);

    backButton.Draw();
}

bool EntitySimulationScene::IsTransparent()const
{
    return false;
}

bool EntitySimulationScene::BlocksUpdate()const
{
    return true;
}

std::string EntitySimulationScene::GetName()const
{
    return "EntitySimulationScene";
}
