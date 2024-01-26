#include "raylib.h"

int main(){

    //Window Dimentions
    const int window_Width {512};
    const int window_Height {380};

    //Initialize the Window
    InitWindow(window_Width, window_Height, "Dapper Dasher");

    //Acceleration due to gravity (pixles per frame, per frame)
    const int gravity{1};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = window_Width/2 - (scarfyRec.width/2);
    scarfyPos.y = window_Height - (scarfyRec.height);

    //Rectangle Dimentions
    const int width {50};
    const int height {80};

    int posY {window_Height - height};
    int velocity {0};

    bool isInAir {};
    //jump velovity
    const int jumpVel {-22};
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        //Start Drawing
        BeginDrawing();
        //Clears Background
        ClearBackground(WHITE);


        //Preform ground check
        if(posY >= window_Height - height){
            //Rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else{
            //Rectangle is in the air
            velocity += gravity;
            isInAir = true;
        }

        //Jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir){    //Subtracting to move up, because window is initialized from the top AND checking if we are NOT in the air
            velocity -= jumpVel;
        }

        //Update Position
        posY += velocity;
        
        DrawRectangle(window_Width/2, posY, width, height, BLUE);

        //Stop Drawing
        EndDrawing();
    }
    CloseWindow();

}