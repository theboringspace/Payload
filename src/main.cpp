#include <cstdlib>
#include <raylib.h>

int main()
{
    InitWindow(1000, 1000, "Payload");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawCircle(500, 500, 50, RAYWHITE);

        EndDrawing();
    }
    CloseWindow();

    return EXIT_SUCCESS;
}
