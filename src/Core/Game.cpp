#include "Game.h"
#include "Events.h"

#include <algorithm>
#include <utility>

Game::Game(EventBus& events_)
:   events(events_)
{
    // One turret splits the stream mid-screen, two flank the goal.
    // Small changes to TURRET_RANGE swing the balance a lot (225 lets ~75% through, 250 ~20%).
    turrets.push_back(Turret({ 700.0f, 540.0f }, TURRET_RANGE));
    turrets.push_back(Turret({ 1250.0f, 250.0f }, TURRET_RANGE));
    turrets.push_back(Turret({ 1250.0f, 830.0f }, TURRET_RANGE));

    spawnTurret = events.Subscribe<SpawnTurret>([this](const SpawnTurret& event)
        {
            turrets.push_back(Turret( {player.GetPosition().x, player.GetPosition().y}, TURRET_RANGE));
        });
}

void Game::SpawnEnemy()
{
    Vector2 spawn{ 0.0f, static_cast<float>(GetRandomValue(ENEMY_SPAWN_MARGIN, WINDOW_HEIGHT - ENEMY_SPAWN_MARGIN)) };
    float speed{ static_cast<float>(GetRandomValue(MIN_ENEMY_SPEED, MAX_ENEMY_SPEED)) };
    enemies.push_back(Enemy(spawn, GOAL, GOAL_RADIUS, speed, DEFAULT_ENEMY_HEALTH));
}

void Game::HandleInput(const InputMap& input)
{
    player.HandleInput(input);
}

void Game::Update(float deltaTime)
{
    // 1. Player
    player.Update(deltaTime);

    // 2. Everything enemies should avoid.
    std::vector<Threat> threats;
    for (const auto& turret : turrets)
    {
        threats.push_back({ turret.GetPosition(), turret.GetRange() * TURRET_THREAT_FACTOR });
    }
    threats.push_back({ player.GetPosition(), PLAYER_THREAT_RADIUS });

    // 3. Steer every enemy before any of them move, so they all react to the same snapshot.
    for (auto& enemy : enemies)
    {
        enemy.Steer(threats, enemies);
    }

    // 4. Turrets
    for (auto& turret : turrets)
    {
        turret.Update(deltaTime);
        turret.TryFire(enemies);
    }

    // 5. Enemies move
    for (auto& enemy : enemies)
    {
        enemy.Update(deltaTime);
    }

    // 6. Record what happened, then remove the dead.
    for (const auto& enemy : enemies)
    {
        if (enemy.IsAlive()) continue;

        if (enemy.ReachedGoal())
        {
            ++results.escaped;
        }
        else
        {
            results.killed.push_back(enemy.GetPosition());
        }
    }
    std::erase_if(enemies, [](const Enemy& enemy) { return !enemy.IsAlive(); });

    // 7. Spawning
    spawnTimer += deltaTime;
    if (spawnTimer >= SPAWN_INTERVAL)
    {
        SpawnEnemy();
        spawnTimer = 0.0f;
    }
}

void Game::Draw()const
{
    // The goal enemies are trying to reach.
    DrawCircleV(GOAL, GOAL_RADIUS, BLUE);

    for (const auto& turret : turrets) turret.Draw();
    for (const auto& enemy : enemies) enemy.Draw();
    player.Draw();
}

GameResults Game::TakeResults()
{
    return std::exchange(results, GameResults{});
}

Vector2 Game::GetGoal()const
{
    return GOAL;
}
