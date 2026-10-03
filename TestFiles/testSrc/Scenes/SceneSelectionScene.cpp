#include "SceneSelectionScene.h"

#include "GameClockDemoScene.h"
#include "SceneDemoScene.h"
#include "EventHandlingScene.h"
#include "SandboxTitleScene.h"

SceneSelectionScene::SceneSelectionScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_)
{
}


void SceneSelectionScene::OnEnter()
{

}
void SceneSelectionScene::OnExit()
{

}
void SceneSelectionScene::OnPause()
{

}
void SceneSelectionScene::OnResume()
{

}

void SceneSelectionScene::Update(float deltaTime)
{
    if (gameClockDemoButton.isClicked())
    {
        manager.Replace(std::make_unique<GameClockDemoScene>(events, manager));
    }
    else if (sceneDemoButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneDemoScene>(events, manager));
    }
    else if (EventHandlingButton.isClicked())
    {
        manager.Replace(std::make_unique<EventHandlingScene>(events, manager));
    }
    else if (titleButton.isClicked())
    {
        manager.Replace(std::make_unique<SandboxTitleScene>(events, manager));
    }

}
void SceneSelectionScene::Draw()
{
    ClearBackground(BLACK);

    gameClockDemoButton.Draw();
    sceneDemoButton.Draw();
    EventHandlingButton.Draw();
    titleButton.Draw();
}

bool SceneSelectionScene::IsTransparent()const
{
    return false;
}
bool SceneSelectionScene::BlocksUpdate()const
{
    return true;
}
