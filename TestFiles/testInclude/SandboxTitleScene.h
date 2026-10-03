#pragma once

#include "SceneManager.h"
#include "Scene.h"
#include "Button.h"

class SandboxTitleScene : public Scene
{
public:
    SandboxTitleScene(SceneManager& manager_);

    virtual ~SandboxTitleScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnPause() override;
    void OnResume() override;

    void Update(float deltaTime) override;
    void Draw() override;

    bool IsTransparent()const override;
    bool BlocksUpdate()const override;

private:
    SceneManager& manager;

    Button startButton;
};
