# Payload
In a world, where SOCIETY branded you as a irredeemable gambling addict -- a nobel science prize has-been. Alone, with a design brought-to-life by the government, you must ensure humanity's survival at all costs.

## Building
Needs CMake 3.24+ and a C++20 compiler. Raylib 5.5 is used if installed, otherwise CMake downloads it.

```
cmake -B build
cmake --build build
```

This builds two programs:
- **Payload**: the real game (`src/Core/main.cpp`).
- **Sandbox**: the same game code plus the test scenes in `TestFiles/`, for trying features out on their own. Press F3 for the debug overlay.

Add `-DENABLE_SANITIZERS=ON` to the first command to build with sanitizers.

## Layout
- `include/`, `src/`: game code (Core, Entities, Events, Scenes, UI).
- `TestFiles/`: Sandbox-only code and test scenes.
- `docs/`: draw.io diagrams.
