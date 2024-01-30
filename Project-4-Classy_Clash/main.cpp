#include "raylib.h"

int main(){

    //Setting the window Dimentions
    const int windowWidth {384};
    const int windowHeight {384};

    //Initializing the window
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    //Loading the Map
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    //Main Game Loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //Draw the map to screen
        Vector2 mapPos {0.0, 0.0};
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        //End Drawing
        EndDrawing();
    }
    //Unloads the Map
    UnloadTexture(map);

    CloseWindow();

}