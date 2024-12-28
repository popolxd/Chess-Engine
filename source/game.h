#ifndef CHESS_H
#define CHESS_H

#include "basic.h"

#define E 2.71828182818

#define PAWN_VALUE 100
#define KNIGHT_VALUE 300
#define BISHOP_VALUE 300
#define ROOK_VALUE 500
#define QUEEN_VALUE 900

#define INF 1000000
#define MATE_VALUE 100000

typedef struct {
    int isSelectedPiece;
    BASIC_Coords selectedPiecePos;
    BASIC_Move possibleMoves[27];
    int possibleMovesLen;

    int eval;
} GAME_UIInfo;

typedef struct {
    int moveCurrentPos;
    int moveScoreQuess;
} GAME_MoveScoreQuess;

void GAME_InitChessboard(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo);

void GAME_DrawGame(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo, BASIC_Coords chessboardPos, int oneBoxSize);
void GAME_DrawChessboard(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo, BASIC_Coords pos, int oneBoxSize);

void GAME_MovePieces(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo, BASIC_Coords pos, int oneBoxSize);

float GAME_Minimax(BASIC_Chessboard* chessboard, int maxDepth, int initialCall, int alpha, int beta, BASIC_Move* bestMove);
float GAME_CaptureSearch(BASIC_Chessboard* chessboard, int alpha, int beta);

void GAME_MoveOrdering(BASIC_Chessboard* chessboard, BASIC_Move* allPossibleMoves, int allPossibleMovesLen);
void GAME_CaptureOrdering(BASIC_Chessboard* chessboard, BASIC_Move* allPossibleMoves, int allPossibleMovesLen);

void GAME_SelectionOrdering(int* moveScoreQuesses, BASIC_Move* movesToOrder, int movesToOrderLen);

int GAME_ReturnEvaluation(BASIC_Chessboard* chessboard);

#endif