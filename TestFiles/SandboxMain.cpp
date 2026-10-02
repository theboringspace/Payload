#include <raylib.h>

#include <memory>
#include <iostream>

#include "SceneManager.h"
#include "SandboxTitleScene.h"
#include "SquareTestScene.h"

#include "GameClock.h"

#include "EventBus.h"
#include "Events.h"
#include "TestPlayer.h"

int main()
{
    InitWindow(1920, 1080, "Payload Sandbox");
    SetTargetFPS(60);

    GameClock clock;

    EventBus events;
    TestPlayer player(events);
    int shownHealth{ 100 };
    events.Subscribe<PlayerDamaged>([&shownHealth](const PlayerDamaged& event)
        {
            shownHealth = event.health;
        });

    SceneManager scenes;
    scenes.Push(std::make_unique<SandboxTitleScene>(scenes));
    scenes.ApplyPending();

    while (!WindowShouldClose() && !scenes.Empty())
    {
        // Initializations
        float dt{ GetFrameTime() };
        dt = std::min(dt, 0.25f);



        // Input
        if (IsKeyPressed(KEY_H))
        {
            player.TakeDamage(10);
        }

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

        DrawText(TextFormat("Health: %d", shownHealth), 500, 400, 40, WHITE);

        EndDrawing();

        // End of Frame
        scenes.ApplyPending();
    }

    CloseWindow();
}
