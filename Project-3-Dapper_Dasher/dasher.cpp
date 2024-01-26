#include "raylib.h"

int main(){

    //Window Dimentions
    const int window_Width {512};
    const int window_Height {380};

    //Initialize the Window
    InitWindow(window_Width, window_Height, "Dapper Dasher");

    //Acceleration due to gravity (pixles per second, per second)
    const int gravity{1'000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = window_Width/2 - (scarfyRec.width/2);
    scarfyPos.y = window_Height - (scarfyRec.height);

    //Animation Frame
    int frame {};
    //Ammount of time before we updat the animation frame
    const float updateTime {1.0/12.0};
    float runningTime {0};

    int velocity {0};

    bool isInAir {};
    //jump velocity (Pixles Per second)
    const int jumpVel {-600};
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){

        //Delta time (time since last frame)
        const float dt {GetFrameTime()};

        //Start Drawing
        BeginDrawing();
        //Clears Background
        ClearBackground(WHITE);


        //Preform ground check
        if(scarfyPos.y >= window_Height - scarfyRec.width){
            //Rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else{
            //Rectangle is in the air
            velocity += gravity * dt;
            isInAir = true;
        }

        //Jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir){    //Addint the negative jump vel, because window is initialized from the top AND checking if we are NOT in the air
            velocity += jumpVel;
        }

        //Update Position
        scarfyPos.y += velocity * dt;
        
        //Update running time
        runningTime += dt;
        if(runningTime >= updateTime){
            runningTime = 0.0;

            //Update Animation Frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if(frame > 5){
                frame = 0;
            }
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        //Stop Drawing
        EndDrawing();
    }
    //Unloads the Scarfy Texture
    UnloadTexture(scarfy);

    CloseWindow();

}