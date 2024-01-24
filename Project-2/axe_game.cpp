#include "raylib.h"
int main(){

    //Window Dimentions
    int windowWidth = 500;
    int windowHeight = 500;

    //Takes 3 inputs, Width, Height, and Title of the window
    InitWindow(windowWidth, windowHeight, "Nikita's Window");

    //Circle Coedinates
    int circle_x = (windowWidth / 2);
    int circle_y = (windowHeight / 2);

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        //Game Logic Begins

        //Draws Circle at the center of the screen
        DrawCircle(circle_x, circle_y, 25, BLUE);

        if(IsKeyDown(KEY_D) && circle_x < windowWidth){
            circle_x = circle_x + 10;
        }
        if(IsKeyDown(KEY_A) && circle_x > 0){
            circle_x = circle_x - 10;
        }
        if(IsKeyDown(KEY_W) && circle_y > 0){
            circle_y = circle_y - 10;
        }
        if(IsKeyDown(KEY_S)&& circle_y < windowHeight){
            circle_y = circle_y + 10;
        }

        //Game Logic Ends
        EndDrawing();
    }
}