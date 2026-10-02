#pragma once

#include <raylib.h>
#include <string>

/**
 * CLASS Button
 * --
 * General-Purpose Button
 * 1. Makes a rectangle.
 * 2. Detects clicks within rectangle.
 * 3. Let others be known that it has been clicked.
 *
 * Basically a rectangle with more steps.
 */
class Button
{
private:
    Rectangle rect;
    std::string text;
    int textSize;
public:
    Button(float x, float y, float width, float height, std::string text_, int textSize);

    bool isClicked()const;
    bool isDown()const;
    void Draw()const;
};
