#pragma once

#include <raylib.h>
#include "EventBus.h"
#include "Constants.h"

class PlayerShip
{
public:
    Vector2 GetPosition()const;

private:
    Vector2 position;

};
