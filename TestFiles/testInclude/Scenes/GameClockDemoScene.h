#pragma once

#include "Constants.h"
#include "EventBus.h"

#include "SceneManager.h"
#include "Scene.h"

#include "Button.h"

#include "Square.h"

class EventSubscription;

class GameClockDemoScene : public Scene
{
public:
    GameClockDemoScene(EventBus& events_, SceneManager& manager_);

    virtual ~GameClockDemoScene() = default;

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
    float shownTimeScale{ 1.0f };

    Button backButton;
    Button increaseTimeScaleButton;
    Button decreaseTimeScaleButton;
    Button increaseFPSButton;
    Button decreaseFPSButton;

    Square square{ 200, {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - 100}, {100, 0}};

    // Events
    EventSubscription timeScaleChanged;
};
