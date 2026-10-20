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
    /// x, y is the top-left corner. Text is centered inside.
    Button(float x, float y, float width, float height, std::string text_, int textSize);

    /// True only on the frame the left mouse button is pressed over the button.
    bool isClicked()const;
    /// True while the left mouse button is held over the button.
    bool isDown()const;
    /// White normally, gray while held.
    void Draw()const;
};
