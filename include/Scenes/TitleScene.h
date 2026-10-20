#pragma once

#include <raylib.h>
#include "Scene.h"

/// The real game's title screen. Just draws "TITLE SCREEN" for now.
class TitleScene : public Scene
{
public:
    virtual ~TitleScene() = default;

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
};
