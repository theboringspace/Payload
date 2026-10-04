#pragma once

#include "EventBus.h"

#include "SceneManager.h"
#include "Scene.h"

#include "Button.h"

class SandboxTitleScene : public Scene
{
public:
    SandboxTitleScene(EventBus& events_, SceneManager& manager_);

    virtual ~SandboxTitleScene() = default;

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
    Button startButton;
};
