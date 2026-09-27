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
    void Push(std::unique_ptr<Scene> scene);
    void Pop();
    void Replace(std::unique_ptr<Scene> scene);
    void Update(float deltaTime);
    void Draw();
    void ApplyPending();
    bool Empty() const;
private:
    std::vector<std::unique_ptr<Scene>> sceneStack_;
    std::vector<PendingOperation> pending_;
};
