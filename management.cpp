#include "raylib.h"
#include "raymath.h"
#include <vector>

class Game 
{
public:
    std::vector<std::vector<Vector2>> paths;
    std::vector<Enemy> enemies;
    std::vector<Turret> turrets;
    float spawnTimer;

    Game() 
    {
        spawnTimer = 0.0f;
        DefinePaths();
        
        // Place a turret in the center of the screen
        turrets.push_back(Turret({400.0f, 300.0f}));
    }

    void DefinePaths() 
    {
        paths.push_back({{0, 100}, {300, 100}, {500, 200}, {800, 200}});
        paths.push_back({{0, 300}, {200, 450}, {600, 150}, {800, 300}});
        paths.push_back({{0, 500}, {400, 500}, {500, 400}, {800, 400}});
    }

    void SpawnEnemy() 
    {
        int randomPath = GetRandomValue(0, 2);
        enemies.push_back(Enemy(paths[randomPath], 100.0f, 3));
    }

    void Update(float deltaTime) 
    {
        spawnTimer += deltaTime;
        if (spawnTimer >= 2.0f) 
        {
            SpawnEnemy();
            spawnTimer = 0.0f;
        }

        for (auto& turret : turrets) 
        {
            turret.Update(deltaTime, enemies);
        }

        for (auto& enemy : enemies) 
        {
            enemy.Update(deltaTime);
        }

        for (auto it = enemies.begin(); it != enemies.end();) 
        {
            if (!it->isAlive) 
            {
                it = enemies.erase(it);
            } 
            else 
            {
                ++it;
            }
        }
    }

    void Draw() {
        for (const auto& path : paths) 
        {
            for (size_t i = 0; i < path.size() - 1; i++) 
            {
                DrawLineEx(path[i], path[i+1], 4.0f, GRAY);
            }
        }

        for (auto& turret : turrets) turret.Draw();
        for (auto& enemy : enemies) enemy.Draw();
    }
};