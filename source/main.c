#include "main.h"
#include "game.h"
#include "basic.h"
#include "textures.h"
#include "raylib.h"

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

int main(void)
{
    SCREEN_WIDTH = 850;
    SCREEN_HEIGHT = 800;

    BASIC_Chessboard chessboard;
    GAME_UIInfo UIInfo;
    GAME_InitChessboard(&chessboard, &UIInfo);

    BASIC_Coords chessboardOffset = (BASIC_Coords){50, 0};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess!");

    SetTargetFPS(60);

    TEXTURES_LoadTextures();

    // Main game loop
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        GAME_MovePieces(&chessboard, &UIInfo, chessboardOffset, 100);
        GAME_DrawGame(&chessboard, &UIInfo, chessboardOffset, 100);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}