#include "raylib.h"
int main(){

    //Window Dimentions
    int windowWidth = 800;
    int windowHeight = 500;

    //Takes 3 inputs, Width, Height, and Title of the window
    InitWindow(windowWidth, windowHeight, "Nikita's Window");

    //Circle Coedinates
    int circle_x {200};
    //int circle_x = (windowWidth / 2);
    int circle_y {200};
    //int circle_y = (windowHeight / 2);

    //"Axe" Cordinates
    int axe_x {400};
    int axe_y {0};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        //Game Logic Begins

        //Draws Circle at the center of the screen
        DrawCircle(circle_x, circle_y, 25, BLUE);
        //Draws a Rectangle axe_x/y for the starting cords, with the width and height of 50 and the color red
        DrawRectangle(axe_x, axe_y, 50, 50, RED);

        //Move the Axe
        axe_y += 10;

        if(IsKeyDown(KEY_D) && circle_x < windowWidth){
            circle_x += 10;
        }
        if(IsKeyDown(KEY_A) && circle_x > 0){
            circle_x -= 10;
        }
        if(IsKeyDown(KEY_W) && circle_y > 0){
            circle_y -= 10;
        }
        if(IsKeyDown(KEY_S)&& circle_y < windowHeight){
            circle_y += 10;
        }

        //Game Logic Ends
        EndDrawing();
    }
}