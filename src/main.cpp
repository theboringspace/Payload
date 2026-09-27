#include <algorithm>
#include <cstdlib>
#include <raylib.h>
#include <string>

// Test Includes
#include "Square.h"
#include "GameClock.h"

int main()
{
    InitWindow(1920, 1080, "Payload");
    // SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    SetTargetFPS(60);

    // TEST CLASS GameClock
    GameClock clock;
    clock.SetTimeScale(5);
    Square square(150, Vector2{0,500},Vector2{100,0});

    while (!WindowShouldClose())
    {
        // Inits
        float dt{ GetFrameTime() };
        dt = std::min(dt, 0.25f);

        // INPUT
        if (IsKeyPressed(KEY_ONE))
        {
            clock.SetTimeScale(1);
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            clock.SetTimeScale(5);
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            clock.SetTimeScale(0.5);
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
            SetTargetFPS(60);
        }
        else if (IsKeyPressed(KEY_FIVE))
        {
            SetTargetFPS(120);
        }
        else if (IsKeyPressed(KEY_SIX))
        {
            SetTargetFPS(1000);
        }

        // UPDATE
        clock.Advance(dt);
        while (clock.ShouldStep())
        {
            square.Update(clock.FIXED_DT);
            clock.ConsumeStep();
        }


        // DRAW
        BeginDrawing();

        ClearBackground(BLACK);
        DrawFPS(0,0);
        std::string text = "Time Scale: " + std::string(TextFormat("%f", clock.GetTimeScale()));
        DrawText(text.c_str(), 0, 50, 25, LIME);
        square.Draw();

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
