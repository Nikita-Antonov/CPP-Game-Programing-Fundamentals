#include "raylib.h"
int main(){

    int windowWidth = 500;
    int windowHeight = 500;

    //Takes 3 inputs, Width, Height, and Title of the window
    //                  int     int         "String"
    InitWindow(windowWidth, windowHeight, "Nikita's Window");

    while(!WindowShouldClose()){
        BeginDrawing();

        DrawCircle(windowWidth / 2, windowHeight / 2, 25, BLUE);

        ClearBackground(RED);
        EndDrawing();
    }
}