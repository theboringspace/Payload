#pragma once

#include "Scene.h"
#include "Button.h"
#include "Constants.h"

#include "EventBus.h"
#include "SceneManager.h"

class SceneSelectionScene : public Scene
{
public:
    SceneSelectionScene(EventBus& events_, SceneManager& manager_);

    void OnEnter()override;
    void OnExit()override;
    void OnPause()override;
    void OnResume()override;

    void HandleInput()override;
    void Update(float deltaTime)override;
    void Draw()override;

    bool IsTransparent()const override;
    bool BlocksUpdate()const override;
private:
    Button gameClockDemoButton {10, 100, 300, 35, "Game Clock Demo", 25};
    Button sceneDemoButton     {10, 200, 300, 35, "Scene Demo", 25};
    Button EventHandlingButton {10, 300, 300, 35, "Event Handling Demo", 25};

    Button titleButton {(WINDOW_WIDTH - 300) / 2.0f, WINDOW_HEIGHT - 150, 300, 35, "Return to Title", 25};
};
