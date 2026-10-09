#include <algorithm>
#include <cstdlib>
#include <memory>

#include <raylib.h>

// Test Includes
#include "GameClock.h"
#include "TitleScene.h"
#include "Scene.h"

int main()
{
    InitWindow(1920, 1080, "Payload");
    SetTargetFPS(120);
    GameClock clock;

    auto scene = std::make_unique<TitleScene>();

    Game game;

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
        game.Update(dt);


        // DRAW
        BeginDrawing();

        scene->Draw();
        game.Draw();

        EndDrawing();
    }

    scene->OnExit();
    scene.reset();
    CloseWindow();

    return EXIT_SUCCESS;
}
