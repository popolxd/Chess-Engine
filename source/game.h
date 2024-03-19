#ifndef CHESS_H
#define CHESS_H

#include "basic.h"

typedef struct {
    int isSelectedPiece;
    BASIC_Coords selectedPiecePos;
    BASIC_Coords possibleMoves[27];
    int possibleMovesLen;
} GAME_UIInfo;

void GAME_InitChessboard(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo);
void GAME_DrawChessboard(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo, BASIC_Coords pos, int oneBoxSize);

void GAME_MovePieces(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo, BASIC_Coords pos, int oneBoxSize);

float GAME_Minimax(BASIC_Chessboard* chessboard, int maxDepth, int initialCall, int alpha, int beta, BASIC_Move* bestMove);
float GAME_CaptureSearch(BASIC_Chessboard* chessboard, int alpha, int beta);

int GAME_ReturnEvaluation(BASIC_Chessboard* chessboard);

#endif