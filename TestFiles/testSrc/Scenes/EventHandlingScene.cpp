#include "EventHandlingScene.h"
#include "Constants.h"
#include "SceneSelectionScene.h"

#include <raylib.h>

EventHandlingScene::EventHandlingScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_),
    backButton(10, 10, 300, 75, "Back to Selection", 30)
{
}

void EventHandlingScene::OnEnter()
{
}
void EventHandlingScene::OnExit()
{
}
void EventHandlingScene::OnPause()
{
}
void EventHandlingScene::OnResume()
{
}

void EventHandlingScene::HandleInput()
{
    if (backButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneSelectionScene>(events, manager));
    }
}
void EventHandlingScene::Update(float deltaTime)
{

}
void EventHandlingScene::Draw()
{
    ClearBackground(BLACK);

    backButton.Draw();
}

bool EventHandlingScene::IsTransparent()const
{
    return false;
}
bool EventHandlingScene::BlocksUpdate()const
{
    return true;
}
