#include "VirtualScreen.h"

#include <algorithm>

#include "Constants.h"

VirtualScreen::VirtualScreen()
:   target_(LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT))
{
    SetTextureFilter(target_.texture, TEXTURE_FILTER_BILINEAR);
}

VirtualScreen::~VirtualScreen()
{
    UnloadRenderTexture(target_);
}

void VirtualScreen::Begin()
{
    BeginTextureMode(target_);
}

void VirtualScreen::End()
{
    EndTextureMode();

    // Largest scale that still fits the whole game in the window.
    const float windowWidth { static_cast<float>(GetScreenWidth()) };
    const float windowHeight{ static_cast<float>(GetScreenHeight()) };
    const float scale{ std::min(windowWidth / WINDOW_WIDTH, windowHeight / WINDOW_HEIGHT) };

    const float width  { WINDOW_WIDTH * scale };
    const float height { WINDOW_HEIGHT * scale };
    const float offsetX{ (windowWidth - width) * 0.5f };
    const float offsetY{ (windowHeight - height) * 0.5f };

    // Map window mouse coordinates back into game coordinates.
    SetMouseOffset(static_cast<int>(-offsetX), static_cast<int>(-offsetY));
    SetMouseScale(1.0f / scale, 1.0f / scale);

    BeginDrawing();
    ClearBackground(BLACK);

    // Render textures are stored upside down, hence the negative height.
    const Rectangle source{ 0.0f, 0.0f, static_cast<float>(WINDOW_WIDTH), -static_cast<float>(WINDOW_HEIGHT) };
    const Rectangle dest  { offsetX, offsetY, width, height };
    DrawTexturePro(target_.texture, source, dest, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

    EndDrawing();
}
