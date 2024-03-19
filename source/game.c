#include "game.h"
#include "main.h"
#include "basic.h"
#include "textures.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>

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

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard->board[i][j] = board[i][j];
        }
    }

    chessboard->whiteKingCastle = 1;
    chessboard->whiteQueenCastle = 1;
    chessboard->blackKingCastle = 1;
    chessboard->blackQueenCastle = 1;

    UIInfo->isSelectedPiece = 0;
    UIInfo->possibleMovesLen = 0;

    chessboard->whiteKingPos = (BASIC_Coords){4, 7};
    chessboard->blackKingPos = (BASIC_Coords){4, 0};

    chessboard->whiteToMove = 1;
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
        DrawRectangle(pos.x + UIInfo->possibleMoves[i].x*oneBoxSize, pos.y + UIInfo->possibleMoves[i].y*oneBoxSize, oneBoxSize, oneBoxSize, BLUE);
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
                // BASIC_GeneratePossibleCapturesForPiece(chessboard, index, UIInfo->possibleMoves, &UIInfo->possibleMovesLen);
                BASIC_GeneratePossibleMovesForPiece(chessboard, index, UIInfo->possibleMoves, &UIInfo->possibleMovesLen);
            }

        } else {
            int isLegal = 0;
            for (int i = 0; i < UIInfo->possibleMovesLen; i++) {
                if (UIInfo->possibleMoves[i].x == index.x && UIInfo->possibleMoves[i].y == index.y) {
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
        float eval = GAME_Minimax(chessboard, 6, 1, -10000000, 100000000, &bestMove);

        BASIC_MovePiece(chessboard, bestMove.startingPos, bestMove.targetPos);
    }
}

float GAME_Minimax(BASIC_Chessboard* chessboard, int maxDepth, int initialCall, int alpha, int beta, BASIC_Move* bestMove)
{
    if (maxDepth == 0) {
        return GAME_ReturnEvaluation(chessboard);
        // return GAME_CaptureSearch(chessboard, -10000000, 100000000);
    }

    BASIC_Chessboard buff = *chessboard;

    int bestEval, currentEval;

    if (chessboard->whiteToMove) {
        bestEval = -10000000;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (BASIC_IsSameColor(chessboard, (BASIC_Coords){j, i}, 1)) {

                    BASIC_Coords selectedPiecePos = (BASIC_Coords){j, i};
                    BASIC_Coords possibleMoves[27];
                    int possibleMovesLen = 0;

                    BASIC_GeneratePossibleMovesForPiece(chessboard, selectedPiecePos, possibleMoves, &possibleMovesLen);

                    for (int k = 0; k < possibleMovesLen; k++) {
                        BASIC_MovePiece(chessboard, selectedPiecePos, possibleMoves[k]);

                        currentEval = GAME_Minimax(chessboard, maxDepth-1, 0, alpha, beta, bestMove);

                        if (currentEval > bestEval) {
                            bestEval = currentEval;
                            if (initialCall) *bestMove = (BASIC_Move){selectedPiecePos, possibleMoves[k]};
                        }

                        if (currentEval > alpha) {
                            alpha = currentEval;
                        }
                        if (beta <= alpha) return bestEval;

                        for (int l = 0; l < 8; l++) { // reset back
                            for (int m = 0; m < 8; m++) {
                                chessboard->board[l][m] = buff.board[l][m];
                            }
                        }
                        
                        *chessboard = buff;
                    }
                }
            }
        }

    } else {
        bestEval = 10000000;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (BASIC_IsSameColor(chessboard, (BASIC_Coords){j, i}, 0)) {
                    BASIC_Coords selectedPiecePos = (BASIC_Coords){j, i};
                    BASIC_Coords possibleMoves[27];
                    int possibleMovesLen = 0;

                    BASIC_GeneratePossibleMovesForPiece(chessboard, selectedPiecePos, possibleMoves, &possibleMovesLen);

                    for (int k = 0; k < possibleMovesLen; k++) {
                        BASIC_MovePiece(chessboard, selectedPiecePos, possibleMoves[k]);

                        currentEval = GAME_Minimax(chessboard, maxDepth-1, 0, alpha, beta, bestMove);

                        if (currentEval < bestEval) {
                            bestEval = currentEval;
                            if (initialCall) *bestMove = (BASIC_Move){selectedPiecePos, possibleMoves[k]};
                        }

                        if (currentEval < beta) {
                            beta = currentEval;
                        }

                        if (beta <= alpha) return bestEval;

                        *chessboard = buff;
                    }
                }
            }
        }
    }

    return bestEval;
}

float GAME_CaptureSearch(BASIC_Chessboard* chessboard, int alpha, int beta)
{
    BASIC_Chessboard buff = *chessboard;

    int bestEval, currentEval;

    if (chessboard->whiteToMove) {
        bestEval = -10000000;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (BASIC_IsSameColor(chessboard, (BASIC_Coords){j, i}, 1)) {

                    BASIC_Coords selectedPiecePos = (BASIC_Coords){j, i};
                    BASIC_Coords possibleMoves[27];
                    int possibleMovesLen = 0;

                    BASIC_GeneratePossibleCapturesForPiece(chessboard, selectedPiecePos, possibleMoves, &possibleMovesLen);

                    for (int k = 0; k < possibleMovesLen; k++) {
                        BASIC_MovePiece(chessboard, selectedPiecePos, possibleMoves[k]);

                        currentEval = GAME_CaptureSearch(chessboard, alpha, beta);

                        if (currentEval > bestEval) {
                            bestEval = currentEval;
                        }

                        if (currentEval > alpha) {
                            alpha = currentEval;
                        }
                        if (beta <= alpha) return bestEval;

                        for (int l = 0; l < 8; l++) { // reset back
                            for (int m = 0; m < 8; m++) {
                                chessboard->board[l][m] = buff.board[l][m];
                            }
                        }
                        
                        *chessboard = buff;
                    }
                }
            }
        }

        if (bestEval == -10000000) {
            return GAME_ReturnEvaluation(chessboard);
        } else {
            return bestEval;
        }

    } else {
        bestEval = 10000000;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (BASIC_IsSameColor(chessboard, (BASIC_Coords){j, i}, 0)) {
                    BASIC_Coords selectedPiecePos = (BASIC_Coords){j, i};
                    BASIC_Coords possibleMoves[27];
                    int possibleMovesLen = 0;

                    BASIC_GeneratePossibleCapturesForPiece(chessboard, selectedPiecePos, possibleMoves, &possibleMovesLen);

                    for (int k = 0; k < possibleMovesLen; k++) {
                        BASIC_MovePiece(chessboard, selectedPiecePos, possibleMoves[k]);

                        currentEval = GAME_CaptureSearch(chessboard, alpha, beta);

                        if (currentEval < bestEval) {
                            bestEval = currentEval;
                        }

                        if (currentEval < beta) {
                            beta = currentEval;
                        }

                        if (beta <= alpha) return bestEval;

                        *chessboard = buff;
                    }
                }
            }
        }

        if (bestEval == 10000000) {
            return GAME_ReturnEvaluation(chessboard);
        } else {
            return bestEval;
        }
    }
}

int knightMap[8][8] = {
    {-20, -10, -20, -10, -10, -20, -10, -20},
    {-20, -10, -10, -5, -5, -10, -10, -20},
    {-10, -5, 0, 5, 5, 0, -5, -10},
    {0, 5, 10, 20, 20, 10, 5, 0},
    {0, 5, 10, 20, 20, 10, 5, 0},
    {-10, -5, 0, 5, 5, 0, -5, -10},
    {-20, -10, -10, -5, -5, -10, -10, -20},
    {-20, -10, -20, -10, -10, -20, -10, -20}
};

int pawnMap[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {30, 30, 30, 30, 30, 30, 30, 30},
    {20, 20, 20, 20, 20, 20, 20, 20},
    {5, 10, 10, 20, 20, 10, 10, 5},
    {5, 0, 10, 20, 20, 10, 0, 5},
    {0, 5, 5, 0, 0, 5, 5, 5},
    {-5, 0, -5, -15, -15, 5, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

int GAME_ReturnEvaluation(BASIC_Chessboard* chessboard)
{
    int eval = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (chessboard->board[i][j]) {
                case 'P':
                    eval += 100 + pawnMap[i][j];
                    break;
                case 'p':
                    eval -= 100 + pawnMap[7-i][j];
                    break;
                case 'N':
                    eval += 300 + knightMap[i][j];
                    break;
                case 'n':
                    eval -= 300 + knightMap[i][j];
                    break;
                case 'B':
                    eval += 300;
                    break;
                case 'b':
                    eval -= 300;
                    break;
                case 'R':
                    eval += 500;
                    break;
                case 'r':
                    eval -= 500;
                    break;
                case 'Q':
                    eval += 900;
                    break;
                case 'q':
                    eval -= 900;
                    break;
                default:
                    break;
            }
        }
    }

    return eval;
}