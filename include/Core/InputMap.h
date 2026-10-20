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
    SLOW_DOWN,

    // Gameplay Actions
    PAUSE,
    UNPAUSE,
    PLACE_TURRET,
    GACHA,

    // Attacks
    FIRE_PROJECTILE,
};

/**
 * CLASS InputMap
 * --
 * Maps Actions to keyboard keys. An Action can have more than one key,
 * and it counts if ANY of its keys match.
 *
 * Typical use:
 *      input.Bind(Action::MOVE_UP, KEY_W);
 *      input.Bind(Action::MOVE_UP, KEY_UP);
 *      if (input.IsDown(Action::MOVE_UP)) { ... }
 */
class InputMap
{
public:
    /// Adds a key to an Action. Doesn't remove keys already bound.
    void Bind(Action action, KeyboardKey key);
    /// True while any bound key is held.
    bool IsDown(Action action)const;
    /// True only on the frame any bound key was pressed.
    bool IsPressed(Action action)const;
    /// True only on the frame any bound key was released.
    bool IsReleased(Action action)const;
    /// Removes every binding.
    void Clear();

private:
    std::unordered_map<Action, std::vector<KeyboardKey>> bindings;
};
