#pragma once

#include <raylib.h>
#include <unordered_map>
#include <vector>

/// Actions that are done on certain inputs. Inputs aren't hardcoded for everything.
/// An input in one scene might have the same Action as an input in another.
enum class Action
{
    // Simple Movement
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,

    // Gameplay Actions
    PAUSE,
    UNPAUSE,
    PLACE_TURRET,
    GACHA,
};

class InputMap
{
public:
    void Bind(Action action, KeyboardKey key);
    bool IsDown(Action action)const;
    bool IsPressed(Action action)const;
    bool IsReleased(Action action)const;
    void Clear();

private:
    std::unordered_map<Action, std::vector<KeyboardKey>> bindings;
};
