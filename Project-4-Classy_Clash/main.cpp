#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{

    // Setting the window Dimentions
    const int windowWidth{384};
    const int windowHeight{384};

    // Initializing the window
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    // Loading the Map
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    // Main Game Loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        // Draw the map to screen
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        // End Drawing
        EndDrawing();
    }
    // Unloads the Map
    UnloadTexture(map);

    CloseWindow();
}