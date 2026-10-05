#include "SceneDemoScene.h"
#include "Constants.h"
#include "SceneSelectionScene.h"

#include <raylib.h>

SceneDemoScene::SceneDemoScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_),
    backButton(10, 10, 300, 75, "Back to Selection", 30)
{
}

void SceneDemoScene::OnEnter()
{
}
void SceneDemoScene::OnExit()
{
}
void SceneDemoScene::OnPause()
{
}
void SceneDemoScene::OnResume()
{
}

void SceneDemoScene::HandleInput()
{
    if (backButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneSelectionScene>(events, manager));
    }
}
void SceneDemoScene::Update(float deltaTime)
{

}
void SceneDemoScene::Draw()
{
    ClearBackground(BLACK);

    backButton.Draw();
}

bool SceneDemoScene::IsTransparent()const
{
    return false;
}
bool SceneDemoScene::BlocksUpdate()const
{
    return true;
}
std::string SceneDemoScene::GetName()const
{
    return "SceneDemoScene";
}
