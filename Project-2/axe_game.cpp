#include "raylib.h"
int main(){

    //Window Dimentions
    int windowWidth = 800;
    int windowHeight = 500;

    //Takes 3 inputs, Width, Height, and Title of the window
    InitWindow(windowWidth, windowHeight, "Nikita's Window");

    //Circle Coedinates
    int circle_x {200};
    int circle_y {200};
    int circle_radius {25};

    //circle edges
    int l_circle_x {circle_x - circle_radius};
    int r_circle_x {circle_x + circle_radius};
    int u_circle_y {circle_y - circle_radius};
    int b_circle_y {circle_y + circle_radius};
    

    //"Axe" Cordinates (The top left corner)
    int axe_x {400};
    int axe_y {0};
    int axe_length {50};

    //Axe Edges
    int l_axe_x {axe_x};                //Left corner of the axe, is already at 0
    int r_axe_x {axe_x + axe_length};
    int u_axe_y {axe_y};                //Upper edge of the corner, is already the variable
    int b_axe_y {axe_y + axe_length};

    int direction {10};

    bool collision_with_axe {true};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();

        ClearBackground(WHITE);

        if(collision_with_axe){
            DrawText("Game Over", windowHeight / 2, windowWidth / 2, 20, RED);
        }
        else{
            //Game Logic Begins

            //Draws Circle at the center of the screen
            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            //Draws a Rectangle axe_x/y for the starting cords, with the width and height of axe_length and the color red
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            //Move the Axe
            axe_y += direction;
            //If the axe reaches the end of the windows height, then it will reverse the direction
            if(axe_y > windowHeight || axe_y < 0){
                direction = -direction;
            }

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
        }
        EndDrawing();
    }
}