#pragma once

#include "EventBus.h"

#include "SceneManager.h"
#include "Scene.h"

#include "Button.h"

class SceneDemoScene : public Scene
{
public:
    SceneDemoScene(EventBus& events_, SceneManager& manager_);

    virtual ~SceneDemoScene() = default;

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
};
