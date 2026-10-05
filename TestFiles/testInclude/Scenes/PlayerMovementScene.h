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
    Vector2 origin{ SIZE.x / 2, SIZE.y / 2 };
    Vector2 velocity{ 0, 0 };
    float direction{ 0.0f }; // Radians

    static constexpr Vector2 SIZE{ 70, 70 };
    static constexpr float ADD_SPEED{ 100.0f };
    static constexpr float START_SPEED{ 10.0f };
    static constexpr float MAX_SPEED{ 300.0f };

    Rectangle square{ position.x + SIZE.x / 2, position.y + SIZE.y / 2, SIZE.x, SIZE.y};

    InputMap input;
};
