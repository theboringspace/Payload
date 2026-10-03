#pragma once

#include "EventBus.h"

#include "SceneManager.h"
#include "Scene.h"

#include "Button.h"

class EventHandlingScene : public Scene
{
public:
    EventHandlingScene(EventBus& events_, SceneManager& manager_);

    virtual ~EventHandlingScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnPause() override;
    void OnResume() override;

    void Update(float deltaTime) override;
    void Draw() override;

    bool IsTransparent()const override;
    bool BlocksUpdate()const override;

private:
    Button backButton;
};
