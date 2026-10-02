#pragma once
#include <raylib.h>
#include <memory>
#include <vector>

#include "Scene.h"

enum class SceneOperation { PUSH, POP, REPLACE };

struct PendingOperation
{
    SceneOperation operation;
    std::unique_ptr<Scene> scene;
};

class SceneManager
{
public:
    /**
     * FUNCTION Push
     * --
     * Queues a PUSH request on pending_, before
     * executing it on sceneStack_ at ApplyPending().
     */
    void Push(std::unique_ptr<Scene> scene);
    /**
     * FUNCTION Pop
     * --
     * Queues a POP request on pending_, to pop the top scene on sceneStack_
     * in ApplyPending().
     */
    void Pop();
    /**
     * FUNCTION Replace
     * --
     * Queues a REPLACE request on pending_, replaces the top scene on sceneStack_
     * in ApplyPending().
     */
    void Replace(std::unique_ptr<Scene> scene);
    /**
     * FUNCTION Update
     * --
     * Updates scenes in sceneStack_ from the top, going down until a scene
     * BlocksUpdate().
     *
     * Includes updating the update-blocking-scene.
     */
    void Update(float deltaTime);
    /**
     * FUNCTION Draw
     * --
     * Finds the lowest scene that needs to be drawn by going down
     * while scenes are flagged transparent, then draws from there
     * all the way to the top.
     *
     * Include drawing the non-transparent scene.
     */
    void Draw();
    /**
     * FUNCTION ApplyPending
     * --
     * Apply all pending operations in pending_ at the end of a frame,
     * after drawing.
     */
    void ApplyPending();
    /**
     * FUNCTION Empty
     * --
     * Returns true if there are no scenes in sceneStack_. False, otherwise.
     */
    bool Empty() const;
private:
    /// Active scenes, owned by the scene manager. back() is the top scene.
    std::vector<std::unique_ptr<Scene>> sceneStack_;
    /// Scene changes requested this frame. Applied in order and cleared in
    /// the ApplyPending() function. Owns any new scenes until they go onto
    /// sceneStack_.
    std::vector<PendingOperation> pendingQueue_;
};
