#include "InputMap.h"
#include <raylib.h>

void InputMap::Bind(Action action, KeyboardKey key)
{
    bindings[action].push_back(key);
}

bool InputMap::IsDown(Action action)const
{
    auto found = bindings.find(action);
    if (found == bindings.end())
    {
        return false;
    }

    for (auto it = found->second.begin(); it != found->second.end(); ++it)
    {
        if(IsKeyDown(*it))
        {
            return true;
        }
    }

    return false;
}

bool InputMap::IsPressed(Action action)const
{
    auto found = bindings.find(action);
    if (found == bindings.end())
    {
        return false;
    }

    for (auto it = found->second.begin(); it != found->second.end(); ++it)
    {
        if(IsKeyPressed(*it))
        {
            return true;
        }
    }

    return false;
}
