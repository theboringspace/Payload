#pragma once

#include "Scene.h"
#include "Button.h"

#include "EventBus.h"
#include "SceneManager.h"

#include "Game.h"

/// Runs Game with no player input, just turrets vs. enemies.
class GameplayTestScene : public Scene
{
public:
    GameplayTestScene(EventBus& events_, SceneManager& manager_);

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

    bool IsTransparent()const override;
    bool BlocksUpdate()const override;
    std::string GetName()const override;

private:
    Button backButton;
    Game game;
};
