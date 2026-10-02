#include "Button.h"
#include <raylib.h>

Button::Button(float x, float y, float width, float height, std::string text_, int textSize_)
:   rect{.x = x, .y = y, .width = width, .height = height}, text{text_}, textSize{textSize_}
{
}

bool Button::isClicked()const
{
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool Button::isDown()const
{
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}


void Button::Draw()const
{
    if (isDown() || isClicked())
    {
        DrawRectangleRec(rect, GRAY);
    }
    else
    {
        DrawRectangleRec(rect, RAYWHITE);
    }
    DrawText(text.c_str(),  rect.x + (rect.width - MeasureText(text.c_str(), textSize)) / 2, rect.y + (rect.height - textSize) / 2, textSize, DARKGRAY);
}
