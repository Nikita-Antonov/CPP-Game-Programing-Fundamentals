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

    //Charecter speed
    float speed {4.0};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");

    Vector2 knightPos {
        (float)windowWidth/2.0f - (4.0f * (0.5f * (float)knight.width/6.0f)),
        (float)windowHeight/2.0f - (4.0f * (0.5f * (float)knight.height))
    };
    //1: facing right, -1: facing left
    float rightLeft {1.0f};
    
    //Animnation Variables
    float runningTime {};
    int frame {};
    const int maxFrames {6};
    const float updateTime {1.0f/12.0f};

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
            //Turnary operator, basically an if/else
            //Condition        if ->               else ->
            direction.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;

            knight = knight_run;
        }else{
            knight = knight_idle;
        }

        //Draw the map to screen
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        //Update Animation Frame
        runningTime += GetFrameTime(); //deltaTime
        if(runningTime >= updateTime){
            frame++;
            runningTime = 0.0f;
            if(frame > maxFrames) frame = 0;
        }

        //Draw the Charecter
        Rectangle source {frame * (float)knight.width/6.0f, 0.0f, rightLeft * (float)knight.width/6.0f, (float)knight.height};
        Rectangle dest {knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};

        DrawTexturePro(knight, source, dest, Vector2 {},0.0f, WHITE);

        //End Drawing
        EndDrawing();
    }
    //Unloads the Map
    UnloadTexture(map);

    CloseWindow();

}