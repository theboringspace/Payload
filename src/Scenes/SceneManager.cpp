#include "SceneManager.h"

void SceneManager::Push(std::unique_ptr<Scene> scene)
{
    pendingQueue_.push_back(PendingOperation(SceneOperation::PUSH, std::move(scene)));
}
void SceneManager::Pop()
{
    pendingQueue_.push_back(PendingOperation(SceneOperation::POP, nullptr));
}
void SceneManager::Replace(std::unique_ptr<Scene> scene)
{
    pendingQueue_.push_back(PendingOperation(SceneOperation::REPLACE, std::move(scene)));
}
void SceneManager::HandleInput()
{
    if (sceneStack_.empty()) return;

    sceneStack_.back()->HandleInput();
}
void SceneManager::Update(float deltaTime)
{
    for (size_t
        index{sceneStack_.size()}; index-- > 0;)
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
    if (sceneStack_.empty()) return;

    size_t lowestVisible{sceneStack_.size() - 1};

    while(lowestVisible > 0 && sceneStack_[lowestVisible]->IsTransparent())
    {
        --lowestVisible;
    }

    for (size_t index{lowestVisible}; index < sceneStack_.size(); ++index)
    {
        sceneStack_[index]->Draw();
    }
}
void SceneManager::ApplyPending()
{
    // Do all queued Scene Operations
    for (auto& sceneOp : pendingQueue_)
    {
        switch(sceneOp.operation)
        {
            case SceneOperation::PUSH :
                if (!sceneStack_.empty())
                {
                    sceneStack_.back()->OnPause();
                }

                sceneStack_.push_back(std::move(sceneOp.scene));
                sceneStack_.back()->OnEnter();

                break;
            case SceneOperation::POP :
                if (sceneStack_.empty())
                {
                    continue;
                }

                sceneStack_.back()->OnExit();
                sceneStack_.pop_back();
                if (!sceneStack_.empty())
                {
                    sceneStack_.back()->OnResume();
                }

                break;
            case SceneOperation::REPLACE :
                if (!sceneStack_.empty())
                {
                    sceneStack_.back()->OnExit();
                    sceneStack_.pop_back();
                }

                sceneStack_.push_back(std::move(sceneOp.scene));
                sceneStack_.back()->OnEnter();

                break;
        }
    }

    pendingQueue_.clear();
}
bool SceneManager::Empty() const
{
    return sceneStack_.empty();
}
