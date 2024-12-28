#include "game.h"
#include "main.h"
#include "basic.h"
#include "textures.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

void GAME_InitChessboard(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo)
{
    char board[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    // char board[8][8] = {
    //     {'-', '-', '-', '-', 'k', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', 'N', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', 'K', '-', '-', '-'}
    // };

    // chessboard->piecesLen = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard->board[i][j] = board[i][j];
            // if (board[i][j] != '-') {
            //     chessboard->pieces[chessboard->piecesLen] = (BASIC_Piece){board[i][j], (BASIC_Coords){j, i}};
            //     chessboard->piecesLen++;
            // }
        }
    }

    chessboard->whiteKingCastle = 1;
    chessboard->whiteQueenCastle = 1;
    chessboard->blackKingCastle = 1;
    chessboard->blackQueenCastle = 1;

    UIInfo->isSelectedPiece = 0;
    UIInfo->possibleMovesLen = 0;
    UIInfo->eval = 0;

    chessboard->whiteKingPos = (BASIC_Coords){4, 7};
    chessboard->blackKingPos = (BASIC_Coords){4, 0};

    chessboard->whiteToMove = 1;
}

void GAME_DrawGame(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo, BASIC_Coords chessboardPos, int oneBoxSize)
{
    DrawRectangle(0, 0, chessboardPos.x, SCREEN_HEIGHT, WHITE);
    float heightOfBar = SCREEN_HEIGHT * (1 / (1 + pow(E, 0.005*UIInfo->eval)));
    DrawRectangle(0, 0, chessboardPos.x, heightOfBar, BLACK);

    if (heightOfBar < SCREEN_HEIGHT - 50) {
        DrawText(TextFormat("%.2f\n", (float)UIInfo->eval/100), 10, SCREEN_HEIGHT - 40, 14, BLACK);
    } else {
        DrawText(TextFormat("%.2f\n", (float)UIInfo->eval/100), 10, SCREEN_HEIGHT - 40, 14, WHITE);
    }
    GAME_DrawChessboard(chessboard, UIInfo, chessboardPos, oneBoxSize);
}

void GAME_DrawChessboard(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo , BASIC_Coords pos, int oneBoxSize)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i+j)%2 == 0) { // biele policko
                DrawRectangle(pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize, NICEWHITE);
            } else {
                DrawRectangle(pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize, NICEBLACK);
            }

        }
    }

    if (UIInfo->isSelectedPiece) {
        DrawRectangle(pos.x + UIInfo->selectedPiecePos.x*oneBoxSize, pos.y + UIInfo->selectedPiecePos.y*oneBoxSize, oneBoxSize, oneBoxSize, RED);
    }

    for (int i = 0; i < UIInfo->possibleMovesLen; i++) {
        DrawRectangle(pos.x + UIInfo->possibleMoves[i].targetPos.x*oneBoxSize, pos.y + UIInfo->possibleMoves[i].targetPos.y*oneBoxSize, oneBoxSize, oneBoxSize, BLUE);
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (chessboard->board[i][j]) {
                case 'P':
                    DrawTexturePro(whitePawn, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'N':
                    DrawTexturePro(whiteKnight, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'B':
                    DrawTexturePro(whiteBishop, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'R':
                    DrawTexturePro(whiteRook, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'Q':
                    DrawTexturePro(whiteQueen, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'K':
                    DrawTexturePro(whiteKing, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'p':
                    DrawTexturePro(blackPawn, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'n':
                    DrawTexturePro(blackKnight, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'b':
                    DrawTexturePro(blackBishop, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'r':
                    DrawTexturePro(blackRook, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'q':
                    DrawTexturePro(blackQueen, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                case 'k':
                    DrawTexturePro(blackKing, (Rectangle){0, 0, 60, 60}, (Rectangle){pos.x + j*oneBoxSize, pos.y + i*oneBoxSize, oneBoxSize, oneBoxSize}, (Vector2){0, 0}, 0, WHITE);
                    break;
                default:
                    break;
            }
        }
    }
}

void GAME_MovePieces(BASIC_Chessboard* chessboard, GAME_UIInfo* UIInfo, BASIC_Coords pos, int oneBoxSize)
{
    if (IsMouseButtonPressed(0)) {
        Vector2 mousePos = GetMousePosition();
        BASIC_Coords index = (BASIC_Coords){(mousePos.x - pos.x)/oneBoxSize, (mousePos.y - pos.y)/oneBoxSize};

        if (!UIInfo->isSelectedPiece) {
            if (BASIC_IsSameColor(chessboard, index, chessboard->whiteToMove)) {
                UIInfo->selectedPiecePos = index;
                UIInfo->isSelectedPiece = 1;
                BASIC_GeneratePossibleMovesForPiece(chessboard, index, UIInfo->possibleMoves, &UIInfo->possibleMovesLen);
            }

        } else {
            int isLegal = 0;
            for (int i = 0; i < UIInfo->possibleMovesLen; i++) {
                if (UIInfo->possibleMoves[i].targetPos.x == index.x && UIInfo->possibleMoves[i].targetPos.y == index.y) {
                    isLegal = 1;
                    break;
                }
            }

            if (isLegal) {
                BASIC_MovePiece(chessboard, UIInfo->selectedPiecePos, index);
            }

            UIInfo->isSelectedPiece = 0;
            UIInfo->possibleMovesLen = 0;
        }
    }

    if (!chessboard->whiteToMove) {
        BASIC_Move bestMove;

        // test
        // time_t time1 = time(NULL);
        // for (int i = 0; i < 50; i++) {
        //     GAME_Minimax(chessboard, 5, 1, -INF, INF, &bestMove);
        // }
        // time_t time2 = time(NULL);

        // printf("%ld\n", time2 - time1);
        // chessboard->whiteToMove = 1;

        UIInfo->eval = GAME_Minimax(chessboard, 5, 1, -INF, INF, &bestMove);

        BASIC_MovePiece(chessboard, bestMove.startingPos, bestMove.targetPos);

        UIInfo->isSelectedPiece = 0;
        UIInfo->possibleMovesLen = 0;
    }
}

float GAME_Minimax(BASIC_Chessboard* chessboard, int maxDepth, int initialCall, int alpha, int beta, BASIC_Move* bestMove)
{
    if (maxDepth == 0) {
        // return GAME_ReturnEvaluation(chessboard);
        return GAME_CaptureSearch(chessboard, alpha, beta);
    }

    BASIC_Chessboard buff = *chessboard;

    int bestEval, currentEval;

    if (chessboard->whiteToMove) {
        bestEval = -INF;

        BASIC_Move allPossibleMoves[218];
        int allPossibleMovesLen = 0;

        BASIC_GenerateAllPossibleMoves(chessboard, allPossibleMoves, &allPossibleMovesLen);

        if (allPossibleMovesLen == 0) {
            if (BASIC_IsWhiteCheck(chessboard)) {
                return -MATE_VALUE-maxDepth;
            } else {
                return 0;
            }
        }

        GAME_MoveOrdering(chessboard, allPossibleMoves, allPossibleMovesLen);

        for (int i = 0; i < allPossibleMovesLen; i++) {
            BASIC_MovePiece(chessboard, allPossibleMoves[i].startingPos, allPossibleMoves[i].targetPos);

            currentEval = GAME_Minimax(chessboard, maxDepth-1, 0, alpha, beta, bestMove);

            *chessboard = buff;

            if (currentEval > bestEval) {
                bestEval = currentEval;
                if (initialCall) *bestMove = allPossibleMoves[i];
            }

            if (currentEval > alpha) {
                alpha = currentEval;
            }
            if (beta <= alpha) return bestEval;
        }

    } else {
        bestEval = INF;

        BASIC_Move allPossibleMoves[218];
        int allPossibleMovesLen = 0;

        BASIC_GenerateAllPossibleMoves(chessboard, allPossibleMoves, &allPossibleMovesLen);

        if (allPossibleMovesLen == 0) {
            if (BASIC_IsBlackCheck(chessboard)) {
                return MATE_VALUE+maxDepth;
            } else {
                return 0;
            }
        }

        GAME_MoveOrdering(chessboard, allPossibleMoves, allPossibleMovesLen);

        for (int i = 0; i < allPossibleMovesLen; i++) {
            BASIC_MovePiece(chessboard, allPossibleMoves[i].startingPos, allPossibleMoves[i].targetPos);

            currentEval = GAME_Minimax(chessboard, maxDepth-1, 0, alpha, beta, bestMove);

            *chessboard = buff;

            if (currentEval < bestEval) {
                bestEval = currentEval;
                if (initialCall) *bestMove = allPossibleMoves[i];
            }

            if (currentEval < beta) {
                beta = currentEval;
            }
            if (beta <= alpha) return bestEval;
        }
    }

    return bestEval;
}

float GAME_CaptureSearch(BASIC_Chessboard* chessboard, int alpha, int beta)
{
    BASIC_Chessboard buff = *chessboard;

    int bestEval, currentEval;

    if (chessboard->whiteToMove) {
        bestEval = GAME_ReturnEvaluation(chessboard);

        BASIC_Move allPossibleCaptures[74];
        int allPossibleCapturesLen = 0;

        BASIC_GenerateAllPossibleCaptures(chessboard, allPossibleCaptures, &allPossibleCapturesLen);
        if (allPossibleCapturesLen == 0) return GAME_ReturnEvaluation(chessboard);

        GAME_CaptureOrdering(chessboard, allPossibleCaptures, allPossibleCapturesLen);

        for (int i = 0; i < allPossibleCapturesLen; i++) {
            BASIC_MovePiece(chessboard, allPossibleCaptures[i].startingPos, allPossibleCaptures[i].targetPos);

            currentEval = GAME_CaptureSearch(chessboard, alpha, beta);

            *chessboard = buff;

            if (currentEval > bestEval) {
                bestEval = currentEval;
            }

            if (currentEval > alpha) {
                alpha = currentEval;
            }
            if (beta <= alpha) return bestEval;
        }

        return bestEval;

    } else {
        bestEval = GAME_ReturnEvaluation(chessboard);

        BASIC_Move allPossibleCaptures[74];
        int allPossibleCapturesLen = 0;

        BASIC_GenerateAllPossibleCaptures(chessboard, allPossibleCaptures, &allPossibleCapturesLen);
        if (allPossibleCapturesLen == 0) return GAME_ReturnEvaluation(chessboard);

        GAME_CaptureOrdering(chessboard, allPossibleCaptures, allPossibleCapturesLen);

        for (int i = 0; i < allPossibleCapturesLen; i++) {
            BASIC_MovePiece(chessboard, allPossibleCaptures[i].startingPos, allPossibleCaptures[i].targetPos);

            currentEval = GAME_CaptureSearch(chessboard, alpha, beta);

            *chessboard = buff;

            if (currentEval < bestEval) {
                bestEval = currentEval;
            }

            if (currentEval < beta) {
                beta = currentEval;
            }

            if (beta <= alpha) return bestEval;
        }

        return bestEval;
    }
}

void GAME_MoveOrdering(BASIC_Chessboard* chessboard, BASIC_Move* allPossibleMoves, int allPossibleMovesLen) // simple capture based move ordering
{
    int moveScoreQuesses[allPossibleMovesLen];

    if (chessboard->whiteToMove) {
        for (int i = 0; i < allPossibleMovesLen; i++) {
            moveScoreQuesses[i] = 0;

            // captures favoring (especially when low value piece captures high value piece)
            if (chessboard->board[allPossibleMoves[i].targetPos.y][allPossibleMoves[i].targetPos.x] != '-') { // doesn't work for en-passant! (irrelevant probably)

                switch (chessboard->board[allPossibleMoves[i].targetPos.y][allPossibleMoves[i].targetPos.x]) {
                    case 'p':
                        moveScoreQuesses[i] += 5 * PAWN_VALUE;
                        break;
                    case 'n':
                        moveScoreQuesses[i] += 5 * KNIGHT_VALUE;
                        break;
                    case 'b':
                        moveScoreQuesses[i] += 5 * BISHOP_VALUE;
                        break;
                    case 'r':
                        moveScoreQuesses[i] += 5 * ROOK_VALUE;
                        break;
                    case 'q':
                        moveScoreQuesses[i] += 5 * QUEEN_VALUE;
                        break;
                }

                switch (chessboard->board[allPossibleMoves[i].startingPos.y][allPossibleMoves[i].startingPos.x]) {
                    case 'P':
                        moveScoreQuesses[i] -= PAWN_VALUE;
                        break;
                    case 'N':
                        moveScoreQuesses[i] -= KNIGHT_VALUE;
                        break;
                    case 'B':
                       moveScoreQuesses[i] -= BISHOP_VALUE;
                        break; 
                    case 'R':
                        moveScoreQuesses[i] -= ROOK_VALUE;
                        break;
                    case 'Q':
                        moveScoreQuesses[i] -= QUEEN_VALUE;
                        break;
                }
            }
        }

    } else {
        for (int i = 0; i < allPossibleMovesLen; i++) {
            moveScoreQuesses[i] = 0;

            // captures favoring (especially when low value piece captures high value piece)
            if (chessboard->board[allPossibleMoves[i].targetPos.y][allPossibleMoves[i].targetPos.x] != '-') { // doesn't work for en-passant! (irrelevant probably)

                switch (chessboard->board[allPossibleMoves[i].targetPos.y][allPossibleMoves[i].targetPos.x]) {
                    case 'P':
                        moveScoreQuesses[i] += 5 * PAWN_VALUE;
                        break;
                    case 'N':
                        moveScoreQuesses[i] += 5 * KNIGHT_VALUE;
                        break;
                    case 'B':
                        moveScoreQuesses[i] += 5 * BISHOP_VALUE;
                        break;
                    case 'R':
                        moveScoreQuesses[i] += 5 * ROOK_VALUE;
                        break;
                    case 'Q':
                        moveScoreQuesses[i] += 5 * QUEEN_VALUE;
                        break;
                }

                switch (chessboard->board[allPossibleMoves[i].startingPos.y][allPossibleMoves[i].startingPos.x]) {
                    case 'p':
                        moveScoreQuesses[i] -= PAWN_VALUE;
                        break;
                    case 'n':
                        moveScoreQuesses[i] -= KNIGHT_VALUE;
                        break;
                    case 'b':
                       moveScoreQuesses[i] -= BISHOP_VALUE;
                        break; 
                    case 'r':
                        moveScoreQuesses[i] -= ROOK_VALUE;
                        break;
                    case 'q':
                        moveScoreQuesses[i] -= QUEEN_VALUE;
                        break;
                }
            }

        }
    }

    GAME_SelectionOrdering(moveScoreQuesses, allPossibleMoves, allPossibleMovesLen);
}

void GAME_CaptureOrdering(BASIC_Chessboard* chessboard, BASIC_Move* allPossibleMoves, int allPossibleMovesLen)
{
    int moveScoreQuesses[allPossibleMovesLen];

    if (chessboard->whiteToMove) {
        for (int i = 0; i < allPossibleMovesLen; i++) {
            moveScoreQuesses[i] = 0;

            switch (chessboard->board[allPossibleMoves[i].targetPos.y][allPossibleMoves[i].targetPos.x]) {
                case 'p':
                    moveScoreQuesses[i] += 5 * PAWN_VALUE;
                    break;
                case 'n':
                    moveScoreQuesses[i] += 5 * KNIGHT_VALUE;
                    break;
                case 'b':
                    moveScoreQuesses[i] += 5 * BISHOP_VALUE;
                    break;
                case 'r':
                    moveScoreQuesses[i] += 5 * ROOK_VALUE;
                    break;
                case 'q':
                    moveScoreQuesses[i] += 5 * QUEEN_VALUE;
                    break;
            }

            switch (chessboard->board[allPossibleMoves[i].startingPos.y][allPossibleMoves[i].startingPos.x]) {
                case 'P':
                    moveScoreQuesses[i] -= PAWN_VALUE;
                    break;
                case 'N':
                    moveScoreQuesses[i] -= KNIGHT_VALUE;
                    break;
                case 'B':
                    moveScoreQuesses[i] -= BISHOP_VALUE;
                    break; 
                case 'R':
                    moveScoreQuesses[i] -= ROOK_VALUE;
                    break;
                case 'Q':
                    moveScoreQuesses[i] -= QUEEN_VALUE;
                    break;
            }
        }

    } else {
        for (int i = 0; i < allPossibleMovesLen; i++) {
            moveScoreQuesses[i] = 0;

            switch (chessboard->board[allPossibleMoves[i].targetPos.y][allPossibleMoves[i].targetPos.x]) {
                case 'P':
                    moveScoreQuesses[i] += 5 * PAWN_VALUE;
                    break;
                case 'N':
                    moveScoreQuesses[i] += 5 * KNIGHT_VALUE;
                    break;
                case 'B':
                    moveScoreQuesses[i] += 5 * BISHOP_VALUE;
                    break;
                case 'R':
                    moveScoreQuesses[i] += 5 * ROOK_VALUE;
                    break;
                case 'Q':
                    moveScoreQuesses[i] += 5 * QUEEN_VALUE;
                    break;
            }

            switch (chessboard->board[allPossibleMoves[i].startingPos.y][allPossibleMoves[i].startingPos.x]) {
                case 'p':
                    moveScoreQuesses[i] -= PAWN_VALUE;
                    break;
                case 'n':
                    moveScoreQuesses[i] -= KNIGHT_VALUE;
                    break;
                case 'b':
                    moveScoreQuesses[i] -= BISHOP_VALUE;
                    break; 
                case 'r':
                    moveScoreQuesses[i] -= ROOK_VALUE;
                    break;
                case 'q':
                    moveScoreQuesses[i] -= QUEEN_VALUE;
                    break;
            }
        }
    }

    GAME_SelectionOrdering(moveScoreQuesses, allPossibleMoves, allPossibleMovesLen);
}

void GAME_SelectionOrdering(int* moveScoreQuesses, BASIC_Move* movesToOrder, int movesToOrderLen) // not really efficient
{
    int maxScoreQuess, maxScoreIndex, maxScoreBuff;
    BASIC_Move movesToOrderBuff;

    for (int i = 0; i < movesToOrderLen - 1; i++) {
        maxScoreQuess = -INF;

        for (int j = i; j < movesToOrderLen; j++) {
            if (moveScoreQuesses[j] > maxScoreQuess) {
                maxScoreQuess = moveScoreQuesses[j];
                maxScoreIndex = j;
            }
        }

        maxScoreBuff = maxScoreQuess;
        moveScoreQuesses[maxScoreIndex] = moveScoreQuesses[i];
        moveScoreQuesses[i] = maxScoreBuff;

        movesToOrderBuff = movesToOrder[maxScoreIndex];
        movesToOrder[maxScoreIndex] = movesToOrder[i];
        movesToOrder[i] = movesToOrderBuff;
    }
}

int pawnMap[8][8] = {
    {0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {5,  5, 10, 25, 25, 10,  5,  5},
    {0,  0,  0, 20, 20,  0,  0,  0},
    {5, -5, -10,  0,  0,-10, -5,  5},
    {5, 10, 10,-20,-20, 10, 10,  5},
    {0,  0,  0,  0,  0,  0,  0,  0}
};

int knightMap[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50},
};

int bishopMap[8][8] = {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20},
};

int rookMap[8][8] = {
    {0,  0,  0,  0,  0,  0,  0,  0},
    {5, 10, 10, 10, 10, 10, 10,  5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {0,  0,  0,  5,  5,  0,  0,  0}
};

int queenMap[8][8] = {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    {-5,  0,  5,  5,  5,  5,  0, -5},
    {0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
};

int kingMiddleGameMap[8][8] = {
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    {20, 20,  0,  0,  0,  0, 20, 20},
    {20, 30, 10,  0,  0, 10, 30, 20}
};

int kingEndGameMap[8][8] = {
    {-50,-40,-30,-20,-20,-30,-40,-50},
    {-30,-20,-10,  0,  0,-10,-20,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-30,  0,  0,  0,  0,-30,-30},
    {-50,-30,-30,-30,-30,-30,-30,-50}
};

int GAME_ReturnEvaluation(BASIC_Chessboard* chessboard)
{
    int eval = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            switch (chessboard->board[i][j]) {
                case 'P':
                    eval += PAWN_VALUE + pawnMap[i][j];
                    break;
                case 'p':
                    eval -= PAWN_VALUE + pawnMap[7-i][j];
                    break;
                case 'N':
                    eval += KNIGHT_VALUE + knightMap[i][j];
                    break;
                case 'n':
                    eval -= KNIGHT_VALUE + knightMap[7-i][j];
                    break;
                case 'B':
                    eval += BISHOP_VALUE + bishopMap[i][j];
                    break;
                case 'b':
                    eval -= BISHOP_VALUE + bishopMap[7-i][j];
                    break;
                case 'R':
                    eval += ROOK_VALUE + rookMap[i][j];
                    break;
                case 'r':
                    eval -= ROOK_VALUE + rookMap[7-i][j];
                    break;
                case 'Q':
                    eval += QUEEN_VALUE + queenMap[i][j];
                    break;
                case 'q':
                    eval -= QUEEN_VALUE + queenMap[7-i][j];
                    break;
                case 'K':
                    eval += kingMiddleGameMap[i][j];
                    break;
                case 'k':
                    eval -= kingMiddleGameMap[7-i][j];
                    break;
                default:
                    break;
            }
        }
    }

    return eval;
}