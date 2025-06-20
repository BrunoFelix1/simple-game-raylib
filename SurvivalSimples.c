#include "raylib.h"
#include <math.h>

#define MONSTERS_SPEED 1.5
#define MAX_MONSTERS 4

typedef struct Player {
    Vector2 position;
    Vector2 size;
    float speed;
    Rectangle rectangle_player;
    Color color;
} Player;

typedef struct Monster {
    Vector2 position;
    float speed;
    float radius;
    bool active;
    Color color;
} Monster;

static void InitGame(int* framesCounter, Player* player, Monster* monsters, bool* pause, int* screenWidth, int* screenHeight);
static void UpdateGame(Music* gameMusic, int* framesCounter, bool* gameOver, bool* pause, Player* player, Monster* monsters, int* screenWidth, int* screenHeight);       
static void DrawGame(Texture2D* textura_player, Texture2D* textura_background, Texture2D* textura_fantasma, int* framesCounter, bool* gameOver, bool* pause, Player* player, Monster* monsters, int* screenHeight, int* screenWidth);         
static void UnloadGame(Music* gameMusic);       
static void UpdateDrawFrame(Texture2D* textura_player, Texture2D* textura_background, Texture2D* textura_fantasma, Music* gameMusic, int* screenWidth, int* screenHeight, int* framesCounter, bool* gameOver, bool* pause, Player* player, Monster* monsters);  

Vector2 MyVector2Subtract(Vector2 v1, Vector2 v2);
Vector2 MyVector2Normalize(Vector2 v);
float MyVector2Distance(Vector2 v1, Vector2 v2);

int main(void)
{
    int screenWidth = 1080;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Monster Survival");
    Texture2D textura_player = LoadTexture("resources/gunslinger.png");
    Texture2D textura_background = LoadTexture("resources/teladefundo.png");
    Texture2D textura_fantasma = LoadTexture("resources/fantasma.png");
    InitAudioDevice();
    Music gameMusic = LoadMusicStream("resources/OldWest.mp3");
    int framesCounter = 0;
    bool gameOver = false;
    bool pause = false;
    Player player = { 0 };
    Monster monsters[MAX_MONSTERS] = { 0 };

    InitGame(&framesCounter, &player, monsters, &pause, &screenWidth, &screenHeight);    SetTargetFPS(60);    while (!WindowShouldClose())    
    {
        UpdateDrawFrame(&textura_player, &textura_background, &textura_fantasma, &gameMusic, &screenWidth, &screenHeight, &framesCounter, &gameOver, &pause, &player, monsters);
    }
    
    UnloadGame(&gameMusic);
    CloseAudioDevice();
    CloseWindow();          return 0;
}

void InitGame(int* framesCounter, Player* player, Monster* monsters, bool* pause, int* screenWidth, int* screenHeight)
{
    int posx, posy;
    bool correctRange = false;    *pause = false;
    *framesCounter = 0;
    
    (*player).size = (Vector2){170, 95};
    (*player).position = (Vector2){*screenWidth / 2 - (*player).size.x / 2, *screenHeight / 2 - (*player).size.y / 2};
    (*player).speed = 3;
    (*player).rectangle_player = (Rectangle){(*player).position.x, (*player).position.y, (*player).size.x, (*player).size.y};    (*player).color = YELLOW;
    
    for (int i = 0; i < MAX_MONSTERS; i++)
    {
        posx = GetRandomValue(0, *screenWidth);

        while (!correctRange)
        {
            if (posx > *screenWidth / 2 - 150 && posx < *screenWidth / 2 + 150)
                posx = GetRandomValue(0, *screenWidth);
            else
                correctRange = true;
        }

        correctRange = false;

        posy = GetRandomValue(0, *screenHeight);

        while (!correctRange)
        {
            if (posy > *screenHeight / 2 - 150 && posy < *screenHeight / 2 + 150)
                posy = GetRandomValue(0, *screenHeight);
            else
                correctRange = true;
        }

        correctRange = false;
        
        monsters[i].position = (Vector2){posx, posy};
        monsters[i].speed = MONSTERS_SPEED;
        monsters[i].radius = 30;
        monsters[i].active = true;
        monsters[i].color = RED;
    }
}

void UpdateGame(Music* gameMusic, int* framesCounter, bool* gameOver, bool* pause, Player* player, Monster* monsters, int* screenWidth, int* screenHeight)
{
    if (!*gameOver)
    {
        UpdateMusicStream(*gameMusic);
        if (IsKeyPressed('P')) 
        {
            *pause = !pause;
            StopMusicStream(*gameMusic);
        }
        if (!*pause)
        {
            PlayMusicStream(*gameMusic);
            *framesCounter = *framesCounter + 1;

            if (IsKeyDown(KEY_UP) && (*player).position.y > 1)
            {
                (*player).position.y -= (*player).speed;
                (*player).rectangle_player.y -= (*player).speed;
            }
            if (IsKeyDown(KEY_DOWN) && (*player).position.y < *screenHeight - (*player).size.y - 1)
            {
                (*player).position.y += (*player).speed;
                (*player).rectangle_player.y += (*player).speed;
            }
            if (IsKeyDown(KEY_LEFT) && (*player).position.x > 1)
            {
                (*player).position.x -= (*player).speed;
                (*player).rectangle_player.x -= (*player).speed;
            }
            if (IsKeyDown(KEY_RIGHT) && (*player).position.x < *screenWidth - (*player).size.x - 3)
            {
                (*player).position.x += (*player).speed;
                (*player).rectangle_player.x += (*player).speed;            }
           
            for (int a = 0; a < MAX_MONSTERS; a++)
            {
                if (CheckCollisionCircleRec(monsters[a].position, monsters[a].radius, (*player).rectangle_player) && monsters[a].active)
                    *gameOver = true;            }

            for (int i = 0; i < MAX_MONSTERS; i++)
            {                if (monsters[i].active)
                {
                    
                    Vector2 direction = MyVector2Subtract((*player).position, monsters[i].position);
                    direction = MyVector2Normalize(direction);
       
                    monsters[i].position.x += monsters[i].speed * direction.x;                    monsters[i].position.y += monsters[i].speed * direction.y;
                    
                
                    for (int j = 0; j < MAX_MONSTERS; j++)
                    {
                        if (i != j && monsters[j].active)
                        {
                            float distance = MyVector2Distance(monsters[i].position, monsters[j].position);
                            float minDistance = monsters[i].radius + monsters[j].radius;                            if (distance < minDistance)
                            {
                                Vector2 separationVector = MyVector2Subtract(monsters[i].position, monsters[j].position);
                                separationVector = MyVector2Normalize(separationVector);

                                monsters[i].position.x += separationVector.x * MONSTERS_SPEED * 0.5;
                                monsters[i].position.y += separationVector.y * MONSTERS_SPEED * 0.5;
                            }
                        }
                    }   
                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame(framesCounter, player, monsters, pause, screenWidth, screenHeight);
            *gameOver = false;
        }
    }
}

void DrawGame(Texture2D* textura_player, Texture2D* textura_background, Texture2D* textura_fantasma, int* framesCounter, bool* gameOver, bool* pause, Player* player, Monster* monsters, int* screenHeight, int* screenWidth)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);    if (!*gameOver)
    {
        DrawRectangleLines(0, 0, *screenWidth, *screenHeight, BLACK);
        DrawRectangleRec((*player).rectangle_player, BLACK);
        DrawTextureEx(*textura_background, (Vector2){0, 0}, 0, 1, RAYWHITE);        DrawTextureEx(*textura_player, (*player).position, 0, 0.7, RAYWHITE);

        for (int i = 0; i < MAX_MONSTERS; i++)
        {
            if (monsters[i].active)
            {
                DrawTextureEx(*textura_fantasma, (Vector2){monsters[i].position.x - monsters[i].radius, monsters[i].position.y - monsters[i].radius}, 0, 0.0584795322, RAYWHITE);
            }
            else
            {
                DrawCircleV(monsters[i].position, monsters[i].radius, Fade(LIGHTGRAY, 0.3f));
            }
        }

        DrawText(TextFormat("TIME: %.02f", (float)*framesCounter / 60), 10, 10, 20, BLACK);

        if (*pause)
        {
            DrawText("GAME PAUSED", *screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, *screenHeight / 2 - 40, 40, GRAY);
        }
    }
    else
    {
        DrawText(TextFormat("VOCÊ FOI PEGO, SOBREVIVEU POR %.02f SEGUNDOS. \n\n\t\tPRESSIONE [ENTER] PARA JOGAR NOVAMENTE", (float)*framesCounter/60), GetScreenWidth() / 2 - MeasureText("VOCÊ FOI PEGO, PRESSIONE [ENTER] PARA JOGAR NOVAMENTE", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
    }

    EndDrawing();
}

void UnloadGame(Music* gameMusic)
{
    UnloadMusicStream(*gameMusic);
}

void UpdateDrawFrame(Texture2D* textura_player, Texture2D* textura_background, Texture2D* textura_fantasma, Music* gameMusic, int* screenWidth, int* screenHeight, int* framesCounter, bool* gameOver, bool* pause, Player* player, Monster* monsters)
{
    UpdateGame(gameMusic, framesCounter, gameOver, pause, player, monsters, screenWidth, screenHeight);
    DrawGame(textura_player, textura_background, textura_fantasma, framesCounter, gameOver, pause, player, monsters, screenHeight, screenWidth);
}

Vector2 MyVector2Subtract(Vector2 v1, Vector2 v2)
{
    Vector2 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    return result;
}

Vector2 MyVector2Normalize(Vector2 v)
{
    float length = sqrtf(v.x * v.x + v.y * v.y);

    if (length == 0)
        return (Vector2){0, 0};
    
    Vector2 result;
    result.x = v.x / length;
    result.y = v.y / length;
    return result;
}

float MyVector2Distance(Vector2 v1, Vector2 v2) {
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return sqrt(dx * dx + dy * dy);
}
