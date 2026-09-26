#pragma once
#include <raylib.h>

struct Square
{
    float side_;
    Vector2 pos_;
    Vector2 vel_;

    void Update(float gameTime)
    {
        pos_.x += vel_.x * gameTime;
        pos_.y += vel_.y * gameTime;
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
