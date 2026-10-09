#include "raylib.h"
#include "raymath.h"
#include <vector>

class Turret 
{
public:
    Vector2 position;
    float range;
    float fireRate;
    float fireTimer;
    int damage;

    Turret(Vector2 pos) 
    {
        position = pos;
        range = 200.0f;
        fireRate = 0.5f;
        fireTimer = 0.0f;
        damage = 1;
    }

    void Update(float deltaTime, std::vector<Enemy>& enemies) 
    {
        if (fireTimer > 0) fireTimer -= deltaTime;

        for (auto& enemy : enemies) 
        {
            if (!enemy.isAlive) continue;

            float distance = Vector2Distance(position, enemy.position);
            if (distance <= range) 
            {
                if (fireTimer <= 0.0f) 
                {
                    enemy.TakeDamage(damage);
                    
                    DrawLineV(position, enemy.position, YELLOW); 
                    
                    fireTimer = fireRate;
                }
                break;
            }
        }
    }

    void Draw() 
    {
        DrawCircleLines(position.x, position.y, range, LIGHTGRAY);
        DrawCircleV(position, 20.0f, BLUE);
    }
};