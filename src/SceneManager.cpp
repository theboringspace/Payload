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
    if (sceneStack_.empty())
    {
        Push(std::move(scene));
    }
    pendingQueue_.push_back(PendingOperation(SceneOperation::REPLACE, std::move(scene)));
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
    size_t springIndex{sceneStack_.size()};;

    for (; sceneStack_[springIndex]->IsTransparent() && springIndex-- > 0;){}

    for (size_t springBack{springIndex}; springBack != sceneStack_.size(); ++springBack)
    {
        sceneStack_[springBack]->Draw();
    }
}
void SceneManager::ApplyPending()
{
    while (!pendingQueue_.empty())
    {
        switch(pendingQueue_.back().operation)
        {
            case SceneOperation::PUSH :
                if (!sceneStack_.empty())
                {
                    sceneStack_.back()->OnPause();
                }

                sceneStack_.push_back(std::move(pendingQueue_.back().scene));
                sceneStack_.back()->OnEnter();

                break;
            case SceneOperation::POP :
                if (sceneStack_.empty())
                {
                    continue;
                }

                sceneStack_.pop_back();
                sceneStack_.back()->OnEnter();

                break;
            case SceneOperation::REPLACE :
                sceneStack_.back()->OnExit();
                sceneStack_.pop_back();

                sceneStack_.push_back(std::move(pendingQueue_.back().scene));
                sceneStack_.back()->OnEnter();

                break;
        }

        pendingQueue_.pop_back();
    }
}
bool SceneManager::Empty() const
{
    return sceneStack_.empty();
}
