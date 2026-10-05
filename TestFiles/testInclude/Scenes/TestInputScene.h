#pragma once

#include <raylib.h>

#include "EventBus.h"

#include "SceneManager.h"
#include "Scene.h"

#include "Button.h"
#include "InputMap.h"

class TestInputScene : public Scene
{
public:
    TestInputScene(EventBus& events_, SceneManager& manager_);

    virtual ~TestInputScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnPause() override;
    void OnResume() override;

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

    bool IsTransparent()const override;
    bool BlocksUpdate()const override;

private:
    /// Draws one row of the action table: name, bound keys, and whether it's held this frame.
    void DrawActionRow(const char* name, const char* keys, Action action, int y)const;

    Button backButton;
    InputMap input;

    // Held input is sampled every frame in HandleInput(), then applied on the fixed step in Update().
    Vector2 moveDirection{ 0.0f, 0.0f };
    Vector2 squarePosition{ 0.0f, 0.0f };
    static constexpr float SQUARE_SIZE{ 50.0f };
    static constexpr float SQUARE_SPEED{ 400.0f };

    // Pressed input counters, so a missed or doubled press is visible.
    bool paused{ false };
    int turretsPlaced{ 0 };
    int gachaPulls{ 0 };
};
