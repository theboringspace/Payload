#include <raylib.h>

#include <memory>
#include <iostream>

#include "SceneManager.h"
#include "SandboxTitleScene.h"

#include "GameClock.h"

#include "EventBus.h"
#include "Events.h"
#include "TestPlayer.h"

int main()
{
    InitWindow(1920, 1080, "Payload Sandbox");
    int targetFPS{ 60 };
    SetTargetFPS(targetFPS);

    EventBus events;
    GameClock clock(events);
    SceneManager scenes;
    scenes.Push(std::make_unique<SandboxTitleScene>(events, scenes));
    scenes.ApplyPending();

    // Subscriptions
    events.Subscribe<IncreaseFPS>([&targetFPS](const IncreaseFPS& event)
        {
            targetFPS += event.increase;
            SetTargetFPS(targetFPS);
        });
    events.Subscribe<DecreaseFPS>([&targetFPS](const DecreaseFPS& event)
        {
            targetFPS -= event.decrease;
            SetTargetFPS(targetFPS);
        });
    events.Subscribe<ResetFPS>([&targetFPS](const ResetFPS& event)
        {
            targetFPS = event.fps;
            SetTargetFPS(targetFPS);
        });

    while (!WindowShouldClose() && !scenes.Empty())
    {
        // Initializations
        float dt{ GetFrameTime() };
        dt = std::min(dt, 0.25f);

        // Input
        scenes.HandleInput();

        // Update
        clock.Advance(dt);
        while (clock.ShouldStep())
        {

            scenes.Update(GameClock::FIXED_DT);
            clock.ConsumeStep();
        }

        // Dispatch all queued Events
        events.Dispatch();


        // Draw
        BeginDrawing();

        scenes.Draw();

        EndDrawing();

        // End of Frame
        scenes.ApplyPending();
    }

    CloseWindow();
}
