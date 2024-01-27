#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight){
    return data.pos.y >= windowHeight - data.rec.height;
}

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

    //Nebula x velocity (pixles per second)
    int nebVel {-200};

    //Array of nebulae
    const int sizeOfNebulae {6};
    AnimData nebulae[sizeOfNebulae] {};

    for(int i = 0; i < sizeOfNebulae; i++){
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = (windowDimentions[1] - nebula.height/8);
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = (1.0/16.0);
        nebulae[i].pos.x = windowDimentions[0] + (i * 300);
    }

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
        if(isOnGround(scarfyData, windowDimentions[1])){
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

        //Update Each Nebula Position
        for(int i = 0; i < sizeOfNebulae; i++){
            nebulae[i].pos.x += nebVel * dt;
        }

        //Update Scarfy Position
        scarfyData.pos.y += velocity * dt;
        
        //=====================================================================================
        //============================|| Updating Animation ||=================================

        for(int i = 0; i < sizeOfNebulae; i++){
            //Update Nebula Running time
            nebulae[i].runningTime += dt;
            if(nebulae[i].runningTime >= nebulae[i].updateTime){
                nebulae[i].runningTime = 0.0;

                //Update Nebula Animation Frame
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if(nebulae[i].frame > 7){
                    nebulae[i].frame = 0;
                }
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
        
        //Draws Nebulae
        for(int i = 0; i < sizeOfNebulae; i++){
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

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