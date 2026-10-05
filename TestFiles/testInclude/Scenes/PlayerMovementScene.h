#pragma once

#include "Constants.h"

#include "EventBus.h"

#include "SceneManager.h"
#include "Scene.h"

#include "InputMap.h"
#include "Button.h"



class PlayerMovementScene : public Scene
{
public:
    PlayerMovementScene(EventBus& events_, SceneManager& manager_);

    virtual ~PlayerMovementScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnPause() override;
    void OnResume() override;

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

    bool IsTransparent()const override;
    bool BlocksUpdate()const override;
    std::string GetName()const override;

private:
    Button backButton;

    Vector2 position{ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f };
    Vector2 velocity{0, 0};

    static constexpr Vector2 SIZE{ 70, 70 };
    static constexpr float SPEED{ 400.0f };

    InputMap input;
};
