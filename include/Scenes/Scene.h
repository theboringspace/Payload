#pragma once

class Scene
{
public:
    virtual ~Scene() = default;

    /// Load all assets on scene entrance.
    virtual void OnEnter();
    /// Unload all assets and such.
    virtual void OnExit();
    ///
    virtual void OnPause();
    virtual void OnResume();

    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    virtual bool IsTransparent()const;
    virtual bool BlocksUpdate()const;
};
