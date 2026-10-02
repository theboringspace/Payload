#pragma once

class Scene
{
public:
    /// Scene objects are always derived, hence it must always have a virtual destructor.
    virtual ~Scene() = default;

    /// Load all assets(textures, spawn the player, start music, ...) on scene entrance.
    virtual void OnEnter();
    /// Unload all assets(textures, spawn the player, start music, ...) and such.
    virtual void OnExit();
    /// Called when there's a scene on top. Pause music, disable update, etc...
    virtual void OnPause();
    /// Called when it is on top again,. Unpause music, disable update, etc...
    virtual void OnResume();

    /// Update everything that's supposed to update in the scene
    virtual void Update(float deltaTime) = 0;
    /// Draw everything that's supposed to be drawain in the scene
    virtual void Draw() = 0;

    /// Is the scene under drawn too? If yes true, else false.
    virtual bool IsTransparent()const;
    /// Scenes below aren't updated.
    virtual bool BlocksUpdate()const;
};
