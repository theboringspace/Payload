#include "SandboxTitleScene.h"
#include "Constants.h"
#include "SceneManager.h"
#include "SceneSelectionScene.h"
#include <raylib.h>

SandboxTitleScene::SandboxTitleScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_),
    startButton((WINDOW_WIDTH - MeasureText("Start Sandbox", 150)), WINDOW_HEIGHT / 2.0f + 100, 400, 175, "Start Sandbox", 50)
{
}


void SandboxTitleScene::OnEnter()
{
}
void SandboxTitleScene::OnExit()
{
}
void SandboxTitleScene::OnPause()
{
}
void SandboxTitleScene::OnResume()
{
}

void SandboxTitleScene::HandleInput()
{
    if (startButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneSelectionScene>(events, manager));
    }
}
void SandboxTitleScene::Update(float deltaTime)
{

}
void SandboxTitleScene::Draw()
{
    ClearBackground(BLACK);

    DrawText("PAYLOAD SANDBOX", (WINDOW_WIDTH - MeasureText("PAYLOAD SANDBOX", 175)) / 2, 250 , 175, RAYWHITE);

    startButton.Draw();
}

bool SandboxTitleScene::IsTransparent()const
{
    return false;
}
bool SandboxTitleScene::BlocksUpdate()const
{
    return true;
}
std::string SandboxTitleScene::GetName()const
{
    return "SandboxTitleScene";
}
