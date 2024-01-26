#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

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

    //AnimData for Nebula
    AnimData nebData { 
        {0.0, 0.0, nebula.width/8, nebula.height/8},                //Rectangle Rec
        {window_Width, window_Height - nebula.height/8},            //Vector2 Pos
        0,                                                          //Int Frame
        (1.0/12.0),                                                 //Float updateTime
        0                                                           //Float runningTime
    };

    //AnimData for Nebula 2
    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8},                //Rectangle Rec
        {window_Width + 300, window_Height - nebula.height/8},      //Vector2 Pos
        0,                                                          //Int Frame
        (1.0/16.0),                                                 //Float updateTime
        0                                                           //Float runningTime
    };

    //Nebula x velocity (pixles per second)
    int nebVel {-200};

    //=====================================================================================
    //=============================|| Scarfy Variables ||==================================
    Texture2D scarfy = LoadTexture("textures/scarfy.png"); //Sprite Sheet is 1x6

    AnimData scarfyData {
        {0.0, 0.0, scarfy.width/6, scarfy.height},                                              //Rectangle Rec
        {window_Width/2 - (scarfyData.rec.width/2), window_Height - (scarfyData.rec.height)},   //Vector2 Pos
        0,                                                                                      //Int Frame
        (1.0/12.0),                                                                             //FLoat updateTime
        0                                                                                       //Float runningTime
    };

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
        if(scarfyData.pos.y >= window_Height - scarfyData.rec.height){
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
        nebData.pos.x += nebVel * dt;

        //Update Nebula 2 Position
        neb2Data.pos.x += nebVel * dt;

        //Update Scarfy Position
        scarfyData.pos.y += velocity * dt;

        
        //=====================================================================================
        //============================|| Updating Animation ||=================================

        //Update Nebula Running time
        nebData.runningTime += dt;
        if(nebData.runningTime >= nebData.updateTime){
            nebData.runningTime = 0.0;

            //Update Nebula Animation Frame
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if(nebData.frame > 7){
                nebData.frame = 0;
            }
        }

        //Update Nebula 2 Running time
        neb2Data.runningTime += dt;
        if(neb2Data.runningTime >= neb2Data.updateTime){
            neb2Data.runningTime = 0.0;

            //Update Nebula Animation Frame
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if(neb2Data.frame > 7){
                neb2Data.frame = 0;
            }
        }

        //Air Check for Scarfy Animation
        if(!isInAir){
            //Update Scarfy running time
            scarfyData.runningTime += dt;
            if(scarfyData.runningTime >= scarfyData.updateTime){
                scarfyData.runningTime = 0.0;

                //Update Scarfy Animation Frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if(scarfyData.frame > 5){
                    scarfyData.frame = 0;
                }
            }
        }
        //=====================================================================================
        
        //Draw Nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);

        //Draw the Second Nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

        //Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        //Stop Drawing
        EndDrawing();
    }
    //Unloads the Scarfy Texture
    UnloadTexture(scarfy);
    //Unloads the Nebula Texture
    UnloadTexture(nebula);

    CloseWindow();

}