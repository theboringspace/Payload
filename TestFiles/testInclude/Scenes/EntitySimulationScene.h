#pragma once

#include "Scene.h"
#include "Button.h"

#include "EventBus.h"
#include "EventSubscription.h"
#include "SceneManager.h"

#include "Game.h"
#include "InputMap.h"

/// Everything together: the player ship, turrets, and free-roaming enemies racing to the goal.
/// Game results are turned into EarthDamaged/EnemyDied events, and the counters on screen
/// are driven by those events.
class EntitySimulationScene : public Scene
{
public:
    EntitySimulationScene(EventBus& events_, SceneManager& manager_);

    void OnEnter() override;
    void OnExit() override;

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

    bool IsTransparent()const override;
    bool BlocksUpdate()const override;
    std::string GetName()const override;

private:
    Button backButton;
    Game game;
    InputMap input;
    Camera2D camera;

    int breached{ 0 };
    int killed{ 0 };

    EventSubscription earthDamagedSubscription;
    EventSubscription enemyDiedSubscription;

    static constexpr int KILL_REWARD{ 1 };
};
