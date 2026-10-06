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
    // Read in HandleInput(), applied in Update()
    float thrustInput{ 0.0f }; // +1 forward (W), -1 reverse (S), 0 none
    float turnInput{ 0.0f };   // -1 left (A), +1 right (D), 0 none
    float direction{ 270.0f }; // Degrees, starts facing up
    Vector2 brakingPower{ 0, 0 }; // How much braking removed on the last Update(), for the readout
    bool braking{ false };

    static constexpr Vector2 SIZE{ 70, 70 };
    static constexpr float ACCELERATION{ 60.0f };         // Velocity gained per second, forward thrust
    static constexpr float REVERSE_ACCELERATION{ 30.0f }; // Velocity gained per second, reverse thrust (weaker)
    static constexpr float TURN_SPEED{ 180.0f };          // Degrees per second
    static constexpr float BRAKE_STRENGTH{ 60.0f }; // Velocity lost per second while braking
    static constexpr float PIXELS{ 10.0f };
    static constexpr float MAX_SPEED{ 100.0f };

    Rectangle square{ position.x, position.y, SIZE.x, SIZE.y};

    InputMap input;
};
