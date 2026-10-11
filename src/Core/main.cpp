#include <algorithm>
#include <cstdlib>
#include <memory>

#include <raylib.h>

// Test Includes
#include "Constants.h"
#include "GameClock.h"
#include "TitleScene.h"
#include "Scene.h"
#include "VirtualScreen.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Payload");
    MaximizeWindow();
    VirtualScreen screen;
    SetTargetFPS(120);
    GameClock clock;

    auto scene = std::make_unique<TitleScene>();

    while (!WindowShouldClose())
    {
        // Inits
        float dt{ GetFrameTime() };
        dt = std::min(dt, 0.25f);


        // UPDATE
        clock.Advance(dt);
        while (clock.ShouldStep())
        {
            scene->Update(GameClock::FIXED_DT);
            clock.ConsumeStep();
        }


        // DRAW
        screen.Begin();

        scene->Draw();

        screen.End();
    }

    scene->OnExit();
    scene.reset();
    CloseWindow();

    return EXIT_SUCCESS;
}
