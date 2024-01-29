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

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame){
    //Update Running time
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime){
        data.runningTime = 0.0;
        //Update Animation Frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame){
            data.frame = 0;
        }
    }

    return data;
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

    float finishLine {nebulae[sizeOfNebulae - 1].pos.x};

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

    //Background Texture
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX {};

    //Midground Texture
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX {};

    //Foreground Texture
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX {};
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){

        //Delta time (time since last frame)
        const float dt {GetFrameTime()};

        //Start Drawing
        BeginDrawing();
        //Clears Background
        ClearBackground(WHITE);

        //Update Background X posituion
        bgX -= 20 * dt;
        mgX -= 40 * dt;
        fgX -= 80 * dt;

        //Resets the texture x posiition when they reach the end of the screen
        if(bgX <= -background.width*2){
            bgX = 0.0;
        }
        if(mgX <= -midground.width*2){
            mgX = 0.0;
        }
        if(fgX <= -foreground.width*2){
            fgX = 0.0f;
        }

        //Draw Background, 2 individual textures, slideing
        Vector2 bg1Pos {bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos {bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        //Draw Midground, 2 individual textures, slideing
        Vector2 mg1Pos {mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos {mgX + background.width*2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        //Draw Foreground, 2 individual textures, slideing
        Vector2 fg1Pos {fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos {fgX + background.width*2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);
        


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

        //Update Finish Line
        finishLine += nebVel * dt;

        //Update Scarfy Position
        scarfyData.pos.y += velocity * dt;
        
        //=====================================================================================
        //============================|| Updating Animation ||=================================

        for(int i = 0; i < sizeOfNebulae; i++){
            nebulae[i] = updateAnimData(nebulae[i], dt, 8);
        }

        //Air Check for Scarfy Animation
        if(!isInAir){
            scarfyData = updateAnimData(scarfyData, dt, 5);
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
    //Unloads the Background
    UnloadTexture(background);
    //Unloads the Midground
    UnloadTexture(midground);
    //Unloads the Foreground
    UnloadTexture(foreground);

    CloseWindow();

}