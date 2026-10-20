#pragma once

#include "EventBus.h"

#include "SceneManager.h"
#include "Scene.h"

#include "Button.h"

/// Placeholder for an event handling demo. Only has a back button for now.
class EventHandlingScene : public Scene
{
public:
    EventHandlingScene(EventBus& events_, SceneManager& manager_);

    virtual ~EventHandlingScene() = default;

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
