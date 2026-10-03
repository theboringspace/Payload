#include "GameClockDemoScene.h"
#include "Constants.h"
#include "SceneSelectionScene.h"

#include <raylib.h>

GameClockDemoScene::GameClockDemoScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_),
    backButton(10, 10, 300, 75, "Back to Selection", 30)
{
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
    if (backButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneSelectionScene>(events, manager));
    }
}
void GameClockDemoScene::Draw()
{
    ClearBackground(BLACK);

    backButton.Draw();
}

bool GameClockDemoScene::IsTransparent()const
{
    return false;
}
bool GameClockDemoScene::BlocksUpdate()const
{
    return true;
}
