#include "TitleScene.h"
#include "Constants.h"
#include <raylib.h>

void TitleScene::OnEnter()
{

}

void TitleScene::OnExit()
{

}

void TitleScene::OnPause()
{

}

void TitleScene::OnResume()
{

}

void TitleScene::HandleInput()
{
}
void TitleScene::Update(float deltaTime)
{

}
void TitleScene::Draw()
{
    ClearBackground(BLACK);

    DrawText("TITLE SCREEN", (WINDOW_WIDTH - MeasureText("TITLE SCREEN", 50)) / 2, WINDOW_HEIGHT / 2 - 25, 50, RAYWHITE);
}

bool TitleScene::IsTransparent()const
{
    return Scene::IsTransparent();
}
bool TitleScene::BlocksUpdate()const
{
    return Scene::BlocksUpdate();
}
