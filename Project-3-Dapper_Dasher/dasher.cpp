#include "raylib.h"

int main(){

    //Window Dimentions
    const int window_Width {512};
    const int window_Height {380};

    //Initialize the Window
    InitWindow(window_Width, window_Height, "Dapper Dasher");

    //Rectangle Dimentions
    const int width {50};
    const int height {80};

    int posY {window_Height - height};
    int velocity {0};
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        //Start Drawing
        BeginDrawing();
        //Clears Background
        ClearBackground(WHITE);

        if(IsKeyPressed(KEY_SPACE)){    //Subtracting to move up, because window is initialized from the top
            velocity -= 10;
        }

        posY += velocity;
        
        DrawRectangle(window_Width/2, posY, width, height, BLUE);

        //Stop Drawing
        EndDrawing();
    }
    CloseWindow();

}