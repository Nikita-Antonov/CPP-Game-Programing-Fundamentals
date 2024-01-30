#include "raylib.h"
#include "raymath.h"

int main(){

    //Setting the window Dimentions
    const int windowWidth {384};
    const int windowHeight {384};

    //Initializing the window
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    //Loading the Map
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos {0.0, 0.0};

    float speed {4.0};

    //Main Game Loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //Creates a direction vector for the charecter movement
        Vector2 direction {};
        if(IsKeyDown(KEY_A)) direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;
        if(Vector2Length(direction) != 0.0){
            //Set mapPos = mapPos - direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        //Draw the map to screen
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        //End Drawing
        EndDrawing();
    }
    //Unloads the Map
    UnloadTexture(map);

    CloseWindow();

}