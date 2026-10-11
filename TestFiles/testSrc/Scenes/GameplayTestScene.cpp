#include "GameplayTestScene.h"
#include "SceneSelectionScene.h"

#include <raylib.h>

GameplayTestScene::GameplayTestScene(EventBus& events_, SceneManager& manager_)
:   Scene(events_, manager_),
    backButton(10, 10, 300, 75, "Back to Selection", 30)
{
}

void GameplayTestScene::HandleInput()
{
    if (backButton.isClicked())
    {
        manager.Replace(std::make_unique<SceneSelectionScene>(events, manager));
    }
}

void GameplayTestScene::Update(float deltaTime)
{
    game.Update(deltaTime);
}

void GameplayTestScene::Draw()
{
    ClearBackground(BLACK);

    game.Draw();
    backButton.Draw();
}

bool GameplayTestScene::IsTransparent()const
{
    return false;
}

bool GameplayTestScene::BlocksUpdate()const
{
    return true;
}

std::string GameplayTestScene::GetName()const
{
    return "GameplayTestScene";
}
