#include "SceneManager.h"

void SceneManager::Push(std::unique_ptr<Scene> scene)
{
    pending_.push_back({PendingOperation(SceneOperation::PUSH, std::move(scene))});
}
void SceneManager::Pop()
{
    pending_.push_back(PendingOperation(SceneOperation::POP, nullptr));
}
void SceneManager::Replace(std::unique_ptr<Scene> scene)
{
    if (sceneStack_.empty())
    {
        Push(std::move(scene));
    }
    pending_.push_back(PendingOperation(SceneOperation::REPLACE, std::move(scene)));
}
void SceneManager::Update(float deltaTime)
{
    for (size_t index{sceneStack_.size()}; index-- > 0;)
    {
        sceneStack_[index]->Update(deltaTime);

        if (sceneStack_[index]->BlocksUpdate())
        {
            return;
        }
    }
}
void SceneManager::Draw()
{
    sceneStack_.back()->Draw();

}
void SceneManager::ApplyPending()
{

}
bool SceneManager::Empty() const
{
    return sceneStack_.empty();
}
