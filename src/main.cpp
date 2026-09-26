#include <algorithm>
#include <cstdlib>
#include <raylib.h>

// Test Includes
#include "Square.h"
#include "GameClock.h"

int main()
{
    InitWindow(1000, 1000, "Payload");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    // TEST CLASS GameClock
    GameClock clock;
    clock.SetTimeScale(0.1);
    Square square(40, Vector2{0,500},Vector2{100,0});

    while (!WindowShouldClose())
    {
        // Inits
        float dt{ GetFrameTime() };
        dt = std::min(dt, 0.25f);

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
        square.Draw();

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
