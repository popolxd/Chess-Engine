#include "textures.h"
#include "raylib.h"

Texture2D whitePawn, whiteKnight, whiteBishop, whiteRook, whiteQueen, whiteKing;
Texture2D blackPawn, blackKnight, blackBishop, blackRook, blackQueen, blackKing;

void TEXTURES_LoadTextures()
{
    whitePawn = LoadTexture("./resources/whitePawn.png");
    whiteKnight = LoadTexture("./resources/whiteKnight.png");
    whiteBishop = LoadTexture("./resources/whiteBishop.png");
    whiteRook = LoadTexture("./resources/whiteRook.png");
    whiteQueen = LoadTexture("./resources/whiteQueen.png");
    whiteKing = LoadTexture("./resources/whiteKing.png");

    blackPawn = LoadTexture("./resources/blackPawn.png");
    blackKnight = LoadTexture("./resources/blackKnight.png");
    blackBishop = LoadTexture("./resources/blackBishop.png");
    blackRook = LoadTexture("./resources/blackRook.png");
    blackQueen = LoadTexture("./resources/blackQueen.png");
    blackKing = LoadTexture("./resources/blackKing.png");
}