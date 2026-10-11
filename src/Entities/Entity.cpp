#include "Entity.h"

Entity::Entity(Vector2 position_)
:   position(position_)
{
}

Vector2 Entity::GetPosition()const
{
    return position;
}

bool Entity::IsActive()const
{
    return active;
}

void Entity::SetPosition(Vector2 position_)
{
    position = position_;
}

void Entity::Deactivate()
{
    active = false;
}
