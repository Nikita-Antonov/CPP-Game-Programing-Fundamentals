#include "raylib.h"

int main(){

    //Window Dimentions
    const int window_Width {512};
    const int window_Height {380};

    //Initialize the Window
    InitWindow(window_Width, window_Height, "Dapper Dasher");

    //Acceleration due to gravity (pixles per second, per second)
    const int gravity{1'000};

    //=====================================================================================
    //=============================|| Nebula Variables ||==================================
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); //Sprite Sheet is 8x8

    //Initialized on same line
    //                 x    y       Width           height
    Rectangle nebRec {0.0, 0.0, nebula.width/8, nebula.height/8};
    //             Position of x       Possition of y
    Vector2 nebPos {window_Width, window_Height - (nebRec.height)};

    Rectangle neb2Rec {0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos {window_Width + 300, window_Height - (nebRec.height)};

    //Nebula Animation Frame
    int nebFrame {};
    const float nebUpdateTime {1.0/12.0};
    float nebRunningTime {0};

    //For second Nebula
    int neb2Frame {};
    const float neb2UpdateTime {1.0/16.0};
    float neb2RunningTime {0};

    //Nebula x velocity (pixles per second)
    int nebVel {-200};

    //=====================================================================================
    //=============================|| Scarfy Variables ||==================================
    Texture2D scarfy = LoadTexture("textures/scarfy.png"); //Sprite Sheet is 1x6

    //Initialized on same line
    //                    x    y       Width           height
    Rectangle scarfyRec {0.0, 0.0, scarfy.width/6, scarfy.height};
    //                          Position of x                       Possition of y
    Vector2 scarfyPos {window_Width/2 - (scarfyRec.width/2), window_Height - (scarfyRec.height)};

    //Scarfy Animation Frame
    int frame {};
    //Ammount of time before we updat the animation frame
    const float updateTime {1.0/12.0};
    float runningTime {0};

    //=====================================================================================

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

        //=================================================================
        //====================|| Position Updates ||=======================

        //Update Nebula Position
        nebPos.x += nebVel * dt;

        //Update Nebula 2 Position
        neb2Pos.x += nebVel * dt;

        //Update Scarfy Position
        scarfyPos.y += velocity * dt;

        
        //=====================================================================================
        //============================|| Updating Animation ||=================================

        //Update Nebula Running time
        nebRunningTime += dt;
        if(nebRunningTime >= nebUpdateTime){
            nebRunningTime = 0.0;

            //Update Nebula Animation Frame
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7){
                nebFrame = 0;
            }
        }

        //Update Nebula 2 Running time
        neb2RunningTime += dt;
        if(neb2RunningTime >= neb2UpdateTime){
            neb2RunningTime = 0.0;

            //Update Nebula Animation Frame
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if(neb2Frame > 7){
                neb2Frame = 0;
            }
        }

        //Air Check for Scarfy Animation
        if(!isInAir){
            //Update Scarfy running time
            runningTime += dt;
            if(runningTime >= updateTime){
                runningTime = 0.0;

                //Update Scarfy Animation Frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if(frame > 5){
                    frame = 0;
                }
            }
        }
        //=====================================================================================
        
        //Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        //Draw the Second Nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        //Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        //Stop Drawing
        EndDrawing();
    }
    //Unloads the Scarfy Texture
    UnloadTexture(scarfy);
    //Unloads the Nebula Texture
    UnloadTexture(nebula);

    CloseWindow();

}