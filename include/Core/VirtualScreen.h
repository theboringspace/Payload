#pragma once

/**
 * CLASS VirtualScreen
 * --
 * Lets the game always draw at WINDOW_WIDTH x WINDOW_HEIGHT, no matter how big the real window is.
 *
 * Everything is drawn to an offscreen texture, which is then scaled to fit the window.
 * Any leftover space becomes black bars, so the aspect ratio never stretches.
 * The mouse is remapped too, so GetMousePosition() still returns game coordinates.
 *
 * Typical use:
 *      screen.Begin();
 *      scene->Draw();
 *      screen.End();
 *
 * Only make one of these after InitWindow().
 */
#include <raylib.h>

class VirtualScreen
{
public:
    VirtualScreen();
    ~VirtualScreen();

    VirtualScreen(const VirtualScreen&) = delete;
    VirtualScreen& operator=(const VirtualScreen&) = delete;

    /**
     * FUNCTION Begin
     * --
     * Start drawing to the virtual screen. Replaces BeginDrawing().
     */
    void Begin();
    /**
     * FUNCTION End
     * --
     * Scale the virtual screen onto the window. Replaces EndDrawing().
     */
    void End();

private:
    RenderTexture2D target_;
};
