#pragma once
#include <raylib.h>
#include <cmath>

struct Square
{
    float side_;
    Vector2 pos_;
    Vector2 vel_;

    void Update(float gameTime)
    {
        pos_.x += vel_.x * gameTime;
        pos_.y += vel_.y * gameTime;

        if (pos_.x + side_ >= 1920)
        {
            vel_.x = -std::abs(vel_.x);
        }
        else if (pos_.x <= 0)
        {
            vel_.x = std::abs(vel_.x);
        }
    }

    Square(float side, Vector2 pos, Vector2 vel)
    :   side_(side), pos_(pos), vel_(vel)
    {
    }

    void Draw()
    {
        DrawRectangle(pos_.x, pos_.y, side_, side_, RAYWHITE);
    }
};
