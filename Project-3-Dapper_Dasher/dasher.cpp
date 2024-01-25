#include "raylib.h"

int main(){

    int window_Width {500};
    int window_Height {500};

    InitWindow(window_Width, window_Height, "Dapper Dasher");
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        
        EndDrawing();
    }

}