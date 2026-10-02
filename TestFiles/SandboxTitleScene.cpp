#include "SandboxTitleScene.h"
#include "Constants.h"
#include "SceneManager.h"
#include "SquareTestScene.h"
#include <raylib.h>

SandboxTitleScene::SandboxTitleScene(SceneManager& manager_)
:   manager(manager_),
    startButton(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 100, 400, 100, "Start Sandbox", 30)
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

void SandboxTitleScene::Update(float deltaTime)
{
    if (startButton.isClicked())
    {
        manager.Replace(std::make_unique<SquareTestScene>(manager));
    }
}
void SandboxTitleScene::Draw()
{
    ClearBackground(BLACK);

    DrawText("SANDBOX TITLE SCREEN", (WINDOW_WIDTH - MeasureText("SANDBOX TITLE SCREEN", 50)) / 2, WINDOW_HEIGHT / 2 - 25, 50, RAYWHITE);

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
