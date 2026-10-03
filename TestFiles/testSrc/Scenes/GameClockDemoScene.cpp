#include "GameClockDemoScene.h"
#include "Constants.h"
#include "SceneSelectionScene.h"

#include "Events.h"

#include <raylib.h>

GameClockDemoScene::GameClockDemoScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_),
    backButton(10, 10, 300, 75, "Back to Selection", 30),
    increaseTimeScaleButton(WINDOW_WIDTH / 2.0f + 10, WINDOW_HEIGHT - 150, 400, 75, "Increase Time Scale", 30),
    decreaseTimeScaleButton(WINDOW_WIDTH / 2.0f - 410, WINDOW_HEIGHT - 150, 400, 75, "Decrease Time Scale", 30),
    increaseFPSButton(WINDOW_WIDTH / 2.0f + 10, WINDOW_HEIGHT - 245, 400, 75, "Increase FPS", 30),
    decreaseFPSButton(WINDOW_WIDTH / 2.0f - 410, WINDOW_HEIGHT - 245, 400, 75, "Decrease FPS", 30)
{
    events_.Subscribe<TimeScaleChanged>([this](const TimeScaleChanged& event)
        {
            shownTimeScale = event.newTimeScale;
        });
}

void GameClockDemoScene::OnEnter()
{
}
void GameClockDemoScene::OnExit()
{
}
void GameClockDemoScene::OnPause()
{
}
void GameClockDemoScene::OnResume()
{
}

void GameClockDemoScene::Update(float deltaTime)
{
    square.Update(deltaTime);

    if (backButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneSelectionScene>(events, manager));
    }
    else if (increaseTimeScaleButton.isClicked())
    {
        events.Enqueue(IncreaseTimeScale{ 0.5f });
    }
    else if (decreaseTimeScaleButton.isClicked())
    {
        events.Enqueue(DecreaseTimeScale{ 0.5f });
    }
    else if (increaseFPSButton.isClicked())
    {
        events.Enqueue(IncreaseFPS{ 30 });
    }
    else if (decreaseFPSButton.isClicked())
    {
        events.Enqueue(DecreaseFPS{ 30 });
    }
}
void GameClockDemoScene::Draw()
{
    ClearBackground(BLACK);

    const char* stats{ TextFormat("Time Scale: %.2fx    FPS: %d", shownTimeScale, GetFPS()) };
    DrawText(stats, (WINDOW_WIDTH - MeasureText(stats, 40)) / 2, 30, 40, RAYWHITE);

    backButton.Draw();
    increaseTimeScaleButton.Draw();
    decreaseTimeScaleButton.Draw();
    increaseFPSButton.Draw();
    decreaseFPSButton.Draw();
    square.Draw();
}

bool GameClockDemoScene::IsTransparent()const
{
    return false;
}
bool GameClockDemoScene::BlocksUpdate()const
{
    return true;
}
