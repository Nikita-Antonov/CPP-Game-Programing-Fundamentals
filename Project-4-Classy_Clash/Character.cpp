#include "Character.h"

Character::Character(){
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{ // Fully qualifying the function (:: <- Scope resolution operator)

    screenPos = {
        (float)winWidth / 2.0f - (4.0f * (0.5f * width)),
        (float)winHeight / 2.0f - (4.0f * (0.5f * height))};
}

void Character::tick(float deltaTime)
{

    worldPosLastFrame = worldPos;

    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;
    if (Vector2Length(direction) != 0.0)
    {
        // Set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // Turnary operator, basically an if/else
        // Condition        if ->               else ->
        direction.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;

        texture = run;
    }
    else
    {
        texture = idle;
    }

    // Update Animation Frame
    runningTime += deltaTime; // deltaTime
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > maxFrames)
            frame = 0;
    }

    // Draw the Charecter
    Rectangle source{frame * width, 0.0f, rightLeft * width / 6.0f, height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};

    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}

void Character::undoMovement(){
    worldPos = worldPosLastFrame;
}