#include <raylib.h>

#include <memory>

#include "SceneManager.h"
#include "SandboxTitleScene.h"
#include "SquareTestScene.h"

#include "GameClock.h"

int main()
{
    InitWindow(1920, 1080, "Payload Sandbox");
    SetTargetFPS(60);

    GameClock clock;

    SceneManager scenes;
    scenes.Push(std::make_unique<SandboxTitleScene>(scenes));
    scenes.ApplyPending();


    while (!WindowShouldClose() && !scenes.Empty())
    {
        // Initializations
        float dt{ GetFrameTime() };
        dt = std::min(dt, 0.25f);

        // Input


        // Update
        clock.Advance(dt);
        while (clock.ShouldStep())
        {
            scenes.Update(GameClock::FIXED_DT);
            clock.ConsumeStep();
        }


        // Draw
        BeginDrawing();

        scenes.Draw();

        EndDrawing();

        // End of Frame
        scenes.ApplyPending();
    }

    CloseWindow();
}
