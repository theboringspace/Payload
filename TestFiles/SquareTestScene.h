#pragma once

#include "Scene.h"

class SquareTestScene : public Scene
{
public:
    virtual ~SquareTestScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnPause() override;
    void OnResume() override;

    void Update(float deltaTime) override;
    void Draw() override;

    bool IsTransparent()const override;
    bool BlocksUpdate()const override;
};
