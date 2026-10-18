#pragma once

#include <raylib.h>
#include <vector>

#include "Constants.h"
#include "Enemy.h"
#include "EventBus.h"
#include "InputMap.h"
#include "PlayerShip.h"
#include "Turret.h"

/// What happened since the last TakeResults() call.
struct GameResults
{
    int escaped{ 0 };              ///< Enemies that reached the goal.
    std::vector<Vector2> killed;   ///< Where each killed enemy died.
};

/// Owns the tower-defense simulation: player, turrets, free-roaming enemies.
/// Deliberately has no dependency on EventBus/SceneManager/Scene so it can
/// be constructed and driven in isolation (e.g. a Sandbox test scene)
/// without standing up the rest of the engine. Scenes turn GameResults into events.
class Game
{
public:
    Game(EventBus& events_);

    /// Passes input to the player. Call every frame.
    void HandleInput(const InputMap& input);
    void Update(float deltaTime);
    void Draw()const;

    /// Returns everything that happened since the last call, then clears it.
    GameResults TakeResults();

    Vector2 GetGoal()const;

    static constexpr float GOAL_RADIUS{ 50.0f };

    const PlayerShip& GetPlayer()const;

private:
    EventBus& events;

    void SpawnEnemy();

    PlayerShip player{ events, PLAYER_SIZE };
    std::vector<Turret> turrets;
    std::vector<Enemy> enemies;
    GameResults results;
    float spawnTimer{ 0.0f };

    static constexpr Vector2 GOAL{ WINDOW_WIDTH - 80.0f, WINDOW_HEIGHT / 2.0f };
    static constexpr float PLAYER_SIZE{ 45.0f };
    static constexpr float PLAYER_THREAT_RADIUS{ 250.0f };
    static constexpr float TURRET_RANGE{ 240.0f };
    static constexpr float TURRET_THREAT_FACTOR{ 1.5f };  // Enemies start avoiding outside the range, so they skirt it instead of diving in

    static constexpr float SPAWN_INTERVAL{ 1.0f };
    static constexpr int MIN_ENEMY_SPEED{ 250 };
    static constexpr int MAX_ENEMY_SPEED{ 600 };
    static constexpr int DEFAULT_ENEMY_HEALTH{ 3 };
    static constexpr int ENEMY_SPAWN_MARGIN{ 20 };       // Keep spawns off the top and bottom edges


    // Events
    EventSubscription spawnTurret;
};
