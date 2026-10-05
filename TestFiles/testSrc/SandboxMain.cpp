#include <raylib.h>

#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "EventSubscription.h"
#include "SceneManager.h"
#include "SandboxTitleScene.h"

#include "GameClock.h"

#include "EventBus.h"
#include "Events.h"
#include "TestPlayer.h"

/// Draws a box in the top-right corner with one line of text per entry.
/// The box sizes itself to fit, so new debug info is just another push_back.
void DrawDebugOverlay(const std::vector<std::string>& lines)
{
    constexpr int FONT_SIZE{ 20 };
    constexpr int LINE_SPACING{ 4 };
    constexpr int PADDING{ 10 };
    constexpr int MARGIN{ 10 };

    int widest{ 0 };
    for (const std::string& line : lines)
    {
        widest = std::max(widest, MeasureText(line.c_str(), FONT_SIZE));
    }

    int width{ widest + PADDING * 2 };
    int height{ static_cast<int>(lines.size()) * (FONT_SIZE + LINE_SPACING) - LINE_SPACING + PADDING * 2 };
    int x{ GetScreenWidth() - width - MARGIN };
    int y{ MARGIN };

    DrawRectangle(x, y, width, height, Fade(BLACK, 0.75f));
    DrawRectangleLines(x, y, width, height, GREEN);

    for (size_t index{ 0 }; index < lines.size(); ++index)
    {
        int lineY{ y + PADDING + static_cast<int>(index) * (FONT_SIZE + LINE_SPACING) };
        DrawText(lines[index].c_str(), x + PADDING, lineY, FONT_SIZE, GREEN);
    }
}

int main()
{
    InitWindow(1920, 1080, "Payload Sandbox");
    int targetFPS{ 60 };
    SetTargetFPS(targetFPS);

    bool debugOn{ false };

    EventBus events;
    GameClock clock(events);
    SceneManager scenes;
    scenes.Push(std::make_unique<SandboxTitleScene>(events, scenes));
    scenes.ApplyPending();

    // Subscriptions
    EventSubscription increaseFPSSub = events.Subscribe<IncreaseFPS>([&targetFPS](const IncreaseFPS& event)
        {
            targetFPS += event.increase;
            SetTargetFPS(targetFPS);
        });
    EventSubscription decreaseFpsSub = events.Subscribe<DecreaseFPS>([&targetFPS](const DecreaseFPS& event)
        {
            targetFPS -= event.decrease;
            SetTargetFPS(targetFPS);
        });
    EventSubscription resetFPSSub = events.Subscribe<ResetFPS>([&targetFPS](const ResetFPS& event)
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

        if (IsKeyPressed(KEY_F3))
        {
            debugOn = !debugOn;
        }


        // Draw
        BeginDrawing();

        scenes.Draw();

        // Debug overlay goes after the scenes so it's always on top.
        if (debugOn)
        {
            std::vector<std::string> debugLines;

            // Raw frame time, not the clamped dt, so hitches show up.
            debugLines.push_back(TextFormat("Frame Time: %.2f ms (%d FPS)", GetFrameTime() * 1000.0f, GetFPS()));

            // Listed top to bottom, so the active scene is first.
            std::vector<std::string> sceneNames{ scenes.GetSceneNames() };
            debugLines.push_back("Scene Stack:");
            for (auto name = sceneNames.rbegin(); name != sceneNames.rend(); ++name)
            {
                debugLines.push_back("  " + *name);
            }

            DrawDebugOverlay(debugLines);
        }

        EndDrawing();

        // End of Frame
        scenes.ApplyPending();
    }

    CloseWindow();
}
