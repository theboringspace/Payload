#include "raylib.h"
#include "raymath.h"
#include <vector>

class Enemy 
{
public:
    Vector2 position;
    float speed;
    int health;
    bool isAlive;
    std::vector<Vector2> path;
    int currentWaypoint;

    Enemy(std::vector<Vector2> selectedPath, float enemySpeed, int maxHealth) 
    {
        path = selectedPath;
        speed = enemySpeed;
        health = maxHealth;
        isAlive = true;
        currentWaypoint = 0;
        
        if (!path.empty()) 
        {
            position = path[0];
        }
    }

    void Update(float deltaTime) 
    {
        if (!isAlive) return;

        if (currentWaypoint < path.size()) 
        {
            Vector2 target = path[currentWaypoint];
            Vector2 direction = Vector2Subtract(target, position);
            float distance = Vector2Length(direction);

            if (distance < 2.0f) 
            {
                currentWaypoint++;
            } 
            else 
            {
                direction = Vector2Normalize(direction);
                position = Vector2Add(position, Vector2Scale(direction, speed * deltaTime));
            }
        } 
        else 
        {
            isAlive = false; 
        }
    }

    void TakeDamage(int amount) 
    {
        health -= amount;
        if (health <= 0) 
        {
            isAlive = false;
        }
    }

    void Draw() 
    {
        if (isAlive) 
        {
            DrawCircleV(position, 15.0f, RED);
        }
    }
};
