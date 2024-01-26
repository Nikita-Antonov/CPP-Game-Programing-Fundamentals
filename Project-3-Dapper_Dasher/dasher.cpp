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
    int windowDimentions[2];
    windowDimentions[0] = 512;  //Width
    windowDimentions[1] = 380;  //Height

    //Initialize the Window
    InitWindow(windowDimentions[0], windowDimentions[1], "Dapper Dasher");

    //Acceleration due to gravity (pixles per second, per second)
    const int gravity{1'000};

    //=====================================================================================
    //=============================|| Nebula Variables ||==================================
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); //Sprite Sheet is 8x8

    //AnimData for Nebula
    AnimData nebData { 
        {0.0, 0.0, nebula.width/8, nebula.height/8},                            //Rectangle Rec
        {windowDimentions[0], windowDimentions[1] - nebula.height/8},           //Vector2 Pos
        0,                                                                      //Int Frame
        (1.0/12.0),                                                             //Float updateTime
        0                                                                       //Float runningTime
    };

    //AnimData for Nebula 2
    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8},                            //Rectangle Rec
        {windowDimentions[0] + 300, windowDimentions[1] - nebula.height/8},     //Vector2 Pos
        0,                                                                      //Int Frame
        (1.0/16.0),                                                             //Float updateTime
        0                                                                       //Float runningTime
    };

    //Nebula x velocity (pixles per second)
    int nebVel {-200};

    //Array of nebulae
    AnimData nebulae[2] { nebData, neb2Data };

    //=====================================================================================
    //=============================|| Scarfy Variables ||==================================
    Texture2D scarfy = LoadTexture("textures/scarfy.png"); //Sprite Sheet is 1x6

    AnimData scarfyData {
        {0.0, 0.0, scarfy.width/6, scarfy.height},                                                          //Rectangle Rec
        {windowDimentions[0]/2 - (scarfyData.rec.width/2), windowDimentions[1] - (scarfyData.rec.height)},  //Vector2 Pos
        0,                                                                                                  //Int Frame
        (1.0/12.0),                                                                                         //FLoat updateTime
        0                                                                                                   //Float runningTime
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
        if(scarfyData.pos.y >= windowDimentions[1] - scarfyData.rec.height){
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
        nebulae[0].pos.x += nebVel * dt;

        //Update Nebula 2 Position
        nebulae[1].pos.x += nebVel * dt;

        //Update Scarfy Position
        scarfyData.pos.y += velocity * dt;

        
        //=====================================================================================
        //============================|| Updating Animation ||=================================

        //Update Nebula Running time
        nebulae[0].runningTime += dt;
        if(nebulae[0].runningTime >= nebulae[0].updateTime){
            nebulae[0].runningTime = 0.0;

            //Update Nebula Animation Frame
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if(nebulae[0].frame > 7){
                nebulae[0].frame = 0;
            }
        }

        //Update Nebula 2 Running time
        nebulae[1].runningTime += dt;
        if(nebulae[1].runningTime >= nebulae[1].updateTime){
            nebulae[1].runningTime = 0.0;

            //Update Nebula Animation Frame
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if(nebulae[1].frame > 7){
                nebulae[1].frame = 0;
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