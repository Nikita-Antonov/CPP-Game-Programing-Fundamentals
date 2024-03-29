#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Character();
    Vector2 getWorldPos() { return worldPos; }

    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
    void undoMovement();

private:
    //Getting Textures
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    Vector2 screenPos {};
    Vector2 worldPos {};

    Vector2 worldPosLastFrame {};

    // 1: facing right, -1: facing left
    float rightLeft{1.0f};

    // Animnation Variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.0f / 12.0f};
    float speed{4.0f};

    float width {};
    float height {};
};