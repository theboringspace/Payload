#include "SquareTestScene.h"
#include "Constants.h"
#include "SandboxTitleScene.h"

#include <raylib.h>

SquareTestScene::SquareTestScene(SceneManager& manager_)
:   manager(manager_),
    backButton(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 100, 400, 100, "Back to Title Sandbox", 30)
{
}

void SquareTestScene::OnEnter()
{

}
void SquareTestScene::OnExit()
{

}
void SquareTestScene::OnPause()
{

}
void SquareTestScene::OnResume()
{

}

void SquareTestScene::Update(float deltaTime)
{
    if (backButton.isClicked())
    {
        manager.Replace(std::make_unique<SandboxTitleScene>(manager));
    }
}
void SquareTestScene::Draw()
{
    ClearBackground(BLACK);

    DrawText("Square Test Scene", 0, 0, 50, RAYWHITE);

    backButton.Draw();
}

bool SquareTestScene::IsTransparent()const
{
    return false;
}
bool SquareTestScene::BlocksUpdate()const
{
    return true;
}
