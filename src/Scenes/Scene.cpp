#include "Scene.h"

Scene::Scene(EventBus& events_, SceneManager& manager_) : events(events_), manager(manager_) {}

void Scene::OnEnter()
{
}

void Scene::OnExit()
{
}

void Scene::OnPause()
{
}

void Scene::OnResume()
{
}

bool Scene::IsTransparent()const
{
    return false;
}

bool Scene::BlocksUpdate()const
{
    return true;
}
