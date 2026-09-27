#pragma once

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void OnEnter();
    virtual void OnExit();
    virtual void OnPause();
    virtual void OnResume();

    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    virtual bool IsTransparent()const;
    virtual bool BlocksUpdate()const;
};
