#include "basic.h"

void BASIC_MovePiece(BASIC_Chessboard* chessboard, BASIC_Coords startingPos, BASIC_Coords targetPos)
{
    // if (chessboard->board[targetPos.y][targetPos.x] != '-') {

    // }

    chessboard->board[targetPos.y][targetPos.x] = chessboard->board[startingPos.y][startingPos.x];

    if (targetPos.x == chessboard->enPassantSquare.x && targetPos.y == chessboard->enPassantSquare.y) {
        if (chessboard->board[startingPos.y][startingPos.x] == 'P') {
            chessboard->board[targetPos.y + 1][targetPos.x] = '-';
        } else if (chessboard->board[startingPos.y][startingPos.x] == 'p') {
            chessboard->board[targetPos.y - 1][targetPos.x] = '-';
        }
    }

    if (targetPos.x == 7 && targetPos.y == 7) chessboard->whiteKingCastle = 0;
    else if (targetPos.x == 0 && targetPos.y == 7) chessboard->whiteQueenCastle = 0;
    else if (targetPos.x == 7 && targetPos.y == 0) chessboard->blackKingCastle = 0;
    else if (targetPos.x == 0 && targetPos.y == 0) chessboard->blackQueenCastle = 0;

    chessboard->enPassantSquare = (BASIC_Coords){-1, -1};

    switch (chessboard->board[startingPos.y][startingPos.x]) {
        case 'K':
            if (startingPos.x - targetPos.x == 2) {
                chessboard->board[7][0] = '-';
                chessboard->board[7][3] = 'R';
            } else if (startingPos.x - targetPos.x == -2) {
                chessboard->board[7][7] = '-';
                chessboard->board[7][5] = 'R';
            }
            chessboard->whiteKingCastle = 0;
            chessboard->whiteQueenCastle = 0;
            chessboard->whiteKingPos = targetPos;
            break;
        case 'k':
            if (startingPos.x - targetPos.x == 2) {
                chessboard->board[0][0] = '-';
                chessboard->board[0][3] = 'r';
            } else if (startingPos.x - targetPos.x == -2) {
                chessboard->board[0][7] = '-';
                chessboard->board[0][5] = 'r';
            }
            chessboard->blackKingCastle = 0;
            chessboard->blackQueenCastle = 0;
            chessboard->blackKingPos = targetPos;
            break;
        case 'P':
            if (startingPos.y - targetPos.y == 2) {
                chessboard->enPassantSquare = (BASIC_Coords){targetPos.x, targetPos.y + 1};
            }
            if (targetPos.y == 0) chessboard->board[targetPos.y][targetPos.x] = 'Q';
            break;
        case 'p':
            if (startingPos.y - targetPos.y == -2) {
                chessboard->enPassantSquare = (BASIC_Coords){targetPos.x, targetPos.y - 1};
            }
            if (targetPos.y == 7) chessboard->board[targetPos.y][targetPos.x] = 'q';
            break;
        case 'R':
            if (startingPos.y == 7) {
                if (startingPos.x == 7) {
                    chessboard->whiteKingCastle = 0;
                } else if (startingPos.x == 0) {
                    chessboard->whiteQueenCastle = 0;
                }
            }
            break;
        case 'r':
            if (startingPos.y == 0) {
                if (startingPos.x == 7) {
                    chessboard->blackKingCastle = 0;
                } else if (startingPos.x == 0) {
                    chessboard->blackQueenCastle = 0;
                }
            }
            break;                   
        default:
            break;
    }

    chessboard->board[startingPos.y][startingPos.x] = '-';
    chessboard->whiteToMove = !chessboard->whiteToMove;
}

void BASIC_GenerateAllPossibleMoves(BASIC_Chessboard* chessboard, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (BASIC_IsSameColor(chessboard, (BASIC_Coords){j, i}, chessboard->whiteToMove)) {
                BASIC_GeneratePossibleMovesForPiece(chessboard, (BASIC_Coords){j, i}, possibleMoves, possibleMovesLen);
            }
        }
    }
}

void BASIC_GenerateAllPossibleCaptures(BASIC_Chessboard* chessboard, BASIC_Move* possibleCaptures, int* possibleCapturesLen)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (BASIC_IsSameColor(chessboard, (BASIC_Coords){j, i}, chessboard->whiteToMove)) {
                BASIC_GeneratePossibleCapturesForPiece(chessboard, (BASIC_Coords){j, i}, possibleCaptures, possibleCapturesLen);
            }
        }
    }
}

void BASIC_GeneratePossibleMovesForPiece(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    switch (chessboard->board[piecePos.y][piecePos.x]) {
        case 'P':
            BASIC_GenerateWhitePawnMoves(chessboard, piecePos, possibleMoves, possibleMovesLen);
            break;
        case 'N':
            BASIC_GenerateKnightMoves(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            break;
        case 'B':
            BASIC_GenerateBishopMoves(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            break;
        case 'R':
            BASIC_GenerateRookMoves(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            break;
        case 'Q':
            BASIC_GenerateBishopMoves(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            BASIC_GenerateRookMoves(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            break;
        case 'K':
            BASIC_GenerateWhiteKingMoves(chessboard, piecePos, possibleMoves, possibleMovesLen);
            break;
        case 'p':
            BASIC_GenerateBlackPawnMoves(chessboard, piecePos, possibleMoves, possibleMovesLen);
            break;
        case 'n':
            BASIC_GenerateKnightMoves(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            break;
        case 'b':
            BASIC_GenerateBishopMoves(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            break;
        case 'r':
            BASIC_GenerateRookMoves(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            break;
        case 'q':
            BASIC_GenerateBishopMoves(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            BASIC_GenerateRookMoves(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            break;
        case 'k':
            BASIC_GenerateBlackKingMoves(chessboard, piecePos, possibleMoves, possibleMovesLen);
            break; 
    }
}

void BASIC_GeneratePossibleCapturesForPiece(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    switch (chessboard->board[piecePos.y][piecePos.x]) {
        case 'P':
            BASIC_GenerateWhitePawnCaptures(chessboard, piecePos, possibleMoves, possibleMovesLen);
            break;
        case 'N':
            BASIC_GenerateKnightCaptures(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            break;
        case 'B':
            BASIC_GenerateBishopCaptures(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            break;
        case 'R':
            BASIC_GenerateRookCaptures(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            break;
        case 'Q':
            BASIC_GenerateBishopCaptures(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            BASIC_GenerateRookCaptures(chessboard, piecePos, 1, possibleMoves, possibleMovesLen);
            break;
        case 'K':
            BASIC_GenerateWhiteKingCaptures(chessboard, piecePos, possibleMoves, possibleMovesLen);
            break;
        case 'p':
            BASIC_GenerateBlackPawnCaptures(chessboard, piecePos, possibleMoves, possibleMovesLen);
            break;
        case 'n':
            BASIC_GenerateKnightCaptures(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            break;
        case 'b':
            BASIC_GenerateBishopCaptures(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            break;
        case 'r':
            BASIC_GenerateRookCaptures(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            break;
        case 'q':
            BASIC_GenerateBishopCaptures(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            BASIC_GenerateRookCaptures(chessboard, piecePos, 0, possibleMoves, possibleMovesLen);
            break;
        case 'k':
            BASIC_GenerateBlackKingCaptures(chessboard, piecePos, possibleMoves, possibleMovesLen);
            break;
    }
}

void BASIC_GenerateBishopMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords currentBoxPos;

    for (int i = 1; i <= min(7 - piecePos.x, 7 - piecePos.y); i++) { // right-down
        currentBoxPos = (BASIC_Coords){piecePos.x + i, piecePos.y + i};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] != '-') break;
    }

    for (int i = 1; i <= min(piecePos.x, 7 - piecePos.y); i++) { // left-down
        currentBoxPos = (BASIC_Coords){piecePos.x - i, piecePos.y + i};
        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] != '-') break;
    }

    for (int i = 1; i <= min(7 - piecePos.x, piecePos.y); i++) { // right-up
        currentBoxPos = (BASIC_Coords){piecePos.x + i, piecePos.y - i};
        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] != '-') break;
    }

    for (int i = 1; i <= min(piecePos.x, piecePos.y); i++) { // left-up
        currentBoxPos = (BASIC_Coords){piecePos.x - i, piecePos.y - i};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] != '-') break;
    }
}

void BASIC_GenerateBishopCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords currentBoxPos;
    for (int i = 1; i <= min(7 - piecePos.x, 7 - piecePos.y); i++) { // right-down
        currentBoxPos = (BASIC_Coords){piecePos.x + i, piecePos.y + i};
        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
        break;
    }

    for (int i = 1; i <= min(piecePos.x, 7 - piecePos.y); i++) { // left-down
        currentBoxPos = (BASIC_Coords){piecePos.x - i, piecePos.y + i};
        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
        break;
    }

    for (int i = 1; i <= min(7 - piecePos.x, piecePos.y); i++) { // right-up
        currentBoxPos = (BASIC_Coords){piecePos.x + i, piecePos.y - i};
        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
        break;
    }

    for (int i = 1; i <= min(piecePos.x, piecePos.y); i++) { // left-up
        currentBoxPos = (BASIC_Coords){piecePos.x - i, piecePos.y - i};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
        break;
    }
}

void BASIC_GenerateRookMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords currentBoxPos;
    for (int i = 1; i <= 7 - piecePos.x; i++) { // right
        currentBoxPos = (BASIC_Coords){piecePos.x + i, piecePos.y};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] != '-') break;
    }

    for (int i = 1; i <= piecePos.x; i++) { // left
        currentBoxPos = (BASIC_Coords){piecePos.x - i, piecePos.y};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] != '-') break;
    }

    for (int i = 1; i <= piecePos.y; i++) { // up
        currentBoxPos = (BASIC_Coords){piecePos.x, piecePos.y - i};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] != '-') break;
    }

    for (int i = 1; i <= 7 - piecePos.y; i++) { // down
        currentBoxPos = (BASIC_Coords){piecePos.x, piecePos.y + i};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] != '-') break;
    }
}

void BASIC_GenerateRookCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords currentBoxPos;
    for (int i = 1; i <= 7 - piecePos.x; i++) { // right
        currentBoxPos = (BASIC_Coords){piecePos.x + i, piecePos.y};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
        break;
    }

    for (int i = 1; i <= piecePos.x; i++) { // left
        currentBoxPos = (BASIC_Coords){piecePos.x - i, piecePos.y};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        
        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
        break;
    }

    for (int i = 1; i <= piecePos.y; i++) { // up
        currentBoxPos = (BASIC_Coords){piecePos.x, piecePos.y - i};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        
        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
        break;
    }

    for (int i = 1; i <= 7 - piecePos.y; i++) { // down
        currentBoxPos = (BASIC_Coords){piecePos.x, piecePos.y + i};

        if (BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) break;

        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        
        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
        break;
    }
}

void BASIC_GenerateKnightMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords possibleDirs[8] = {
        (BASIC_Coords){-2, -1}, (BASIC_Coords){-1, -2}, (BASIC_Coords){2, -1}, (BASIC_Coords){1, -2},
        (BASIC_Coords){-2, 1}, (BASIC_Coords){-1, 2}, (BASIC_Coords){2, 1}, (BASIC_Coords){1, 2}
    };

    BASIC_Coords currentBoxPos;
    for (int i = 0; i < 8; i++) {
        currentBoxPos = (BASIC_Coords){piecePos.x + possibleDirs[i].x, piecePos.y + possibleDirs[i].y};

        if (currentBoxPos.x < 0 || currentBoxPos.x > 7 || currentBoxPos.y < 0 || currentBoxPos.y > 7 || BASIC_IsSameColor(chessboard, currentBoxPos, isWhite)) continue;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
    }
}

void BASIC_GenerateKnightCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords possibleDirs[8] = {
        (BASIC_Coords){-2, -1}, (BASIC_Coords){-1, -2}, (BASIC_Coords){2, -1}, (BASIC_Coords){1, -2},
        (BASIC_Coords){-2, 1}, (BASIC_Coords){-1, 2}, (BASIC_Coords){2, 1}, (BASIC_Coords){1, 2}
    };

    BASIC_Coords currentBoxPos;
    for (int i = 0; i < 8; i++) {
        currentBoxPos = (BASIC_Coords){piecePos.x + possibleDirs[i].x, piecePos.y + possibleDirs[i].y};

        if (currentBoxPos.x < 0 || currentBoxPos.x > 7 || currentBoxPos.y < 0 || currentBoxPos.y > 7 || !BASIC_IsSameColor(chessboard, currentBoxPos, !isWhite)) continue;

        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, isWhite, possibleMoves, possibleMovesLen);
    }
}

void BASIC_GenerateWhitePawnMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    if (chessboard->board[piecePos.y - 1][piecePos.x] == '-') {
        BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x, piecePos.y - 1}, 1, possibleMoves, possibleMovesLen);

        if (piecePos.y == 6 && chessboard->board[piecePos.y - 2][piecePos.x] == '-') {
            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x, piecePos.y - 2}, 1, possibleMoves, possibleMovesLen);
        }
    }

    char buff;
    if (piecePos.x > 0) {
        if (BASIC_IsSameColor(chessboard, (BASIC_Coords){piecePos.x - 1, piecePos.y - 1}, 0)) {

            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x - 1, piecePos.y - 1}, 1, possibleMoves, possibleMovesLen);

        } else if  (chessboard->enPassantSquare.x == piecePos.x - 1 && chessboard->enPassantSquare.y == piecePos.y - 1 && chessboard->board[piecePos.y - 1][piecePos.x - 1] == '-') {
            
            buff = chessboard->board[piecePos.y][piecePos.x - 1];
            chessboard->board[piecePos.y][piecePos.x - 1] = '-';
            chessboard->board[piecePos.y - 1][piecePos.x - 1] = chessboard->board[piecePos.y][piecePos.x];
            chessboard->board[piecePos.y][piecePos.x] = '-';
            if (!BASIC_IsWhiteCheck(chessboard)) {
                possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){piecePos.x - 1, piecePos.y - 1}};
                (*possibleMovesLen)++;
            }
            chessboard->board[piecePos.y][piecePos.x - 1] = buff;
            chessboard->board[piecePos.y][piecePos.x] = chessboard->board[piecePos.y - 1][piecePos.x - 1];
            chessboard->board[piecePos.y - 1][piecePos.x - 1] = '-';
        }
    }

    if (piecePos.x < 7) {
        if (BASIC_IsSameColor(chessboard, (BASIC_Coords){piecePos.x + 1, piecePos.y - 1}, 0)) {

            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x + 1, piecePos.y - 1}, 1, possibleMoves, possibleMovesLen);

        } else if (chessboard->enPassantSquare.x == piecePos.x + 1 && chessboard->enPassantSquare.y == piecePos.y - 1 && chessboard->board[piecePos.y - 1][piecePos.x + 1] == '-') {
            
            buff = chessboard->board[piecePos.y][piecePos.x + 1];
            chessboard->board[piecePos.y][piecePos.x + 1] = '-';
            chessboard->board[piecePos.y - 1][piecePos.x + 1] = chessboard->board[piecePos.y][piecePos.x];
            chessboard->board[piecePos.y][piecePos.x] = '-';
            if (!BASIC_IsWhiteCheck(chessboard)) {
                possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){piecePos.x + 1, piecePos.y - 1}};
                (*possibleMovesLen)++;
            }
            chessboard->board[piecePos.y][piecePos.x + 1] = buff;
            chessboard->board[piecePos.y][piecePos.x] = chessboard->board[piecePos.y - 1][piecePos.x + 1];
            chessboard->board[piecePos.y - 1][piecePos.x + 1] = '-';
        }
    }
}

void BASIC_GenerateWhitePawnCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    char buff;
    if (piecePos.x > 0) {
        if (BASIC_IsSameColor(chessboard, (BASIC_Coords){piecePos.x - 1, piecePos.y - 1}, 0)) {

            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x - 1, piecePos.y - 1}, 1, possibleMoves, possibleMovesLen);

        } else if  (chessboard->enPassantSquare.x == piecePos.x - 1 && chessboard->enPassantSquare.y == piecePos.y - 1 && chessboard->board[piecePos.y - 1][piecePos.x - 1] == '-') {
            
            buff = chessboard->board[piecePos.y][piecePos.x - 1];
            chessboard->board[piecePos.y][piecePos.x - 1] = '-';
            chessboard->board[piecePos.y - 1][piecePos.x - 1] = chessboard->board[piecePos.y][piecePos.x];
            chessboard->board[piecePos.y][piecePos.x] = '-';
            if (!BASIC_IsWhiteCheck(chessboard)) {
                possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){piecePos.x - 1, piecePos.y - 1}};
                (*possibleMovesLen)++;
            }
            chessboard->board[piecePos.y][piecePos.x - 1] = buff;
            chessboard->board[piecePos.y][piecePos.x] = chessboard->board[piecePos.y - 1][piecePos.x - 1];
            chessboard->board[piecePos.y - 1][piecePos.x - 1] = '-';
        }
    }

    if (piecePos.x < 7) {
        if (BASIC_IsSameColor(chessboard, (BASIC_Coords){piecePos.x + 1, piecePos.y - 1}, 0)) {

            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x + 1, piecePos.y - 1}, 1, possibleMoves, possibleMovesLen);

        } else if (chessboard->enPassantSquare.x == piecePos.x + 1 && chessboard->enPassantSquare.y == piecePos.y - 1 && chessboard->board[piecePos.y - 1][piecePos.x + 1] == '-') {
            
            buff = chessboard->board[piecePos.y][piecePos.x + 1];
            chessboard->board[piecePos.y][piecePos.x + 1] = '-';
            chessboard->board[piecePos.y - 1][piecePos.x + 1] = chessboard->board[piecePos.y][piecePos.x];
            chessboard->board[piecePos.y][piecePos.x] = '-';
            if (!BASIC_IsWhiteCheck(chessboard)) {
                possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){piecePos.x + 1, piecePos.y - 1}};;
                (*possibleMovesLen)++;
            }
            chessboard->board[piecePos.y][piecePos.x + 1] = buff;
            chessboard->board[piecePos.y][piecePos.x] = chessboard->board[piecePos.y - 1][piecePos.x + 1];
            chessboard->board[piecePos.y - 1][piecePos.x + 1] = '-';
        }
    }
}

void BASIC_GenerateBlackPawnMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    if (chessboard->board[piecePos.y + 1][piecePos.x] == '-') {

        BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x, piecePos.y + 1}, 0, possibleMoves, possibleMovesLen);

        if (piecePos.y == 1 && chessboard->board[piecePos.y + 2][piecePos.x] == '-') {

            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x, piecePos.y + 2}, 0, possibleMoves, possibleMovesLen);
        }
    }

    char buff;
    if (piecePos.x > 0) {         
        if (BASIC_IsSameColor(chessboard, (BASIC_Coords){piecePos.x - 1, piecePos.y + 1}, 1)) {

            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x - 1, piecePos.y + 1}, 0, possibleMoves, possibleMovesLen);

        } else if (chessboard->enPassantSquare.x == piecePos.x - 1 && chessboard->enPassantSquare.y == piecePos.y + 1 && chessboard->board[piecePos.y + 1][piecePos.x - 1] == '-') {
            
            buff = chessboard->board[piecePos.y][piecePos.x - 1];
            chessboard->board[piecePos.y][piecePos.x - 1] = '-';
            chessboard->board[piecePos.y + 1][piecePos.x - 1] = chessboard->board[piecePos.y][piecePos.x];
            chessboard->board[piecePos.y][piecePos.x] = '-';
            if (!BASIC_IsBlackCheck(chessboard)) {
                possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){piecePos.x - 1, piecePos.y + 1}};;
                (*possibleMovesLen)++;
            }
            chessboard->board[piecePos.y][piecePos.x - 1] = buff;
            chessboard->board[piecePos.y][piecePos.x] = chessboard->board[piecePos.y + 1][piecePos.x - 1];
            chessboard->board[piecePos.y + 1][piecePos.x - 1] = '-';
        }
    }

    if (piecePos.x < 7) {
        if (BASIC_IsSameColor(chessboard, (BASIC_Coords){piecePos.x + 1, piecePos.y + 1}, 1)) {

            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x + 1, piecePos.y + 1}, 0, possibleMoves, possibleMovesLen);

        } else if (chessboard->enPassantSquare.x == piecePos.x + 1 && chessboard->enPassantSquare.y == piecePos.y + 1 && chessboard->board[piecePos.y + 1][piecePos.x + 1] == '-') {
            
            buff = chessboard->board[piecePos.y][piecePos.x + 1];
            chessboard->board[piecePos.y][piecePos.x + 1] = '-';
            chessboard->board[piecePos.y + 1][piecePos.x + 1] = chessboard->board[piecePos.y][piecePos.x];
            chessboard->board[piecePos.y][piecePos.x] = '-';
            if (!BASIC_IsBlackCheck(chessboard)) {
                possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){piecePos.x + 1, piecePos.y + 1}};;
                (*possibleMovesLen)++;
            }
            chessboard->board[piecePos.y][piecePos.x + 1] = buff;
            chessboard->board[piecePos.y][piecePos.x] = chessboard->board[piecePos.y + 1][piecePos.x + 1];
            chessboard->board[piecePos.y + 1][piecePos.x + 1] = '-';
        }
    }
}

void BASIC_GenerateBlackPawnCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    char buff;
    if (piecePos.x > 0) {         
        if (BASIC_IsSameColor(chessboard, (BASIC_Coords){piecePos.x - 1, piecePos.y + 1}, 1)) {

            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x - 1, piecePos.y + 1}, 0, possibleMoves, possibleMovesLen);

        } else if (chessboard->enPassantSquare.x == piecePos.x - 1 && chessboard->enPassantSquare.y == piecePos.y + 1 && chessboard->board[piecePos.y + 1][piecePos.x - 1] == '-') {
            
            buff = chessboard->board[piecePos.y][piecePos.x - 1];
            chessboard->board[piecePos.y][piecePos.x - 1] = '-';
            chessboard->board[piecePos.y + 1][piecePos.x - 1] = chessboard->board[piecePos.y][piecePos.x];
            chessboard->board[piecePos.y][piecePos.x] = '-';
            if (!BASIC_IsBlackCheck(chessboard)) {
                possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){piecePos.x - 1, piecePos.y + 1}};;
                (*possibleMovesLen)++;
            }
            chessboard->board[piecePos.y][piecePos.x - 1] = buff;
            chessboard->board[piecePos.y][piecePos.x] = chessboard->board[piecePos.y + 1][piecePos.x - 1];
            chessboard->board[piecePos.y + 1][piecePos.x - 1] = '-';
        }
    }

    if (piecePos.x < 7) {
        if (BASIC_IsSameColor(chessboard, (BASIC_Coords){piecePos.x + 1, piecePos.y + 1}, 1)) {

            BASIC_AddPossibleMove(chessboard, piecePos, (BASIC_Coords){piecePos.x + 1, piecePos.y + 1}, 0, possibleMoves, possibleMovesLen);

        } else if (chessboard->enPassantSquare.x == piecePos.x + 1 && chessboard->enPassantSquare.y == piecePos.y + 1 && chessboard->board[piecePos.y + 1][piecePos.x + 1] == '-') {
            
            buff = chessboard->board[piecePos.y][piecePos.x + 1];
            chessboard->board[piecePos.y][piecePos.x + 1] = '-';
            chessboard->board[piecePos.y + 1][piecePos.x + 1] = chessboard->board[piecePos.y][piecePos.x];
            chessboard->board[piecePos.y][piecePos.x] = '-';
            if (!BASIC_IsBlackCheck(chessboard)) {
                possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){piecePos.x + 1, piecePos.y + 1}};;
                (*possibleMovesLen)++;
            }
            chessboard->board[piecePos.y][piecePos.x + 1] = buff;
            chessboard->board[piecePos.y][piecePos.x] = chessboard->board[piecePos.y + 1][piecePos.x + 1];
            chessboard->board[piecePos.y + 1][piecePos.x + 1] = '-';
        }
    }
}

void BASIC_GenerateWhiteKingMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords possibleDirs[8] = {
        (BASIC_Coords){-1, -1}, (BASIC_Coords){-1, 0}, (BASIC_Coords){-1, 1}, (BASIC_Coords){0, -1},
        (BASIC_Coords){0, 1}, (BASIC_Coords){1, -1}, (BASIC_Coords){1, 0}, (BASIC_Coords){1, 1}
    };

    BASIC_Coords currentBoxPos;
    for (int i = 0; i < 8; i++) {
        currentBoxPos = (BASIC_Coords){piecePos.x + possibleDirs[i].x, piecePos.y + possibleDirs[i].y};
        if (currentBoxPos.x < 0 || currentBoxPos.x > 7 || currentBoxPos.y < 0 || currentBoxPos.y > 7 || BASIC_IsSameColor(chessboard, currentBoxPos, 1)) continue;

        chessboard->whiteKingPos = currentBoxPos;
        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, 1, possibleMoves, possibleMovesLen);
        chessboard->whiteKingPos = piecePos;
    }

    if (!BASIC_IsWhiteCheck(chessboard)) {
        if (chessboard->whiteKingCastle && chessboard->board[7][5] == '-' && chessboard->board[7][6] == '-') {

            chessboard->board[7][5] = 'K';
            chessboard->board[7][4] = '-';
            chessboard->whiteKingPos = (BASIC_Coords){5, 7};

            if (!BASIC_IsWhiteCheck(chessboard)) {
                chessboard->board[7][6] = 'K';
                chessboard->board[7][5] = '-';
                chessboard->whiteKingPos = (BASIC_Coords){6, 7};

                if (!BASIC_IsWhiteCheck(chessboard)) {
                    possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){6, 7}};
                    (*possibleMovesLen)++;
                }
            }
            chessboard->board[7][6] = '-';
            chessboard->board[7][5] = '-';
            chessboard->board[7][4] = 'K';
            chessboard->whiteKingPos = (BASIC_Coords){4, 7};

        }
        if (chessboard->whiteQueenCastle && chessboard->board[7][3] == '-' && chessboard->board[7][2] == '-') {

            chessboard->board[7][3] = 'K';
            chessboard->board[7][4] = '-';
            chessboard->whiteKingPos = (BASIC_Coords){3, 7};

            if (!BASIC_IsWhiteCheck(chessboard)) {
                chessboard->board[7][2] = 'K';
                chessboard->board[7][3] = '-';
                chessboard->whiteKingPos = (BASIC_Coords){2, 7};

                if (!BASIC_IsWhiteCheck(chessboard)) {
                    possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){2, 7}};
                    (*possibleMovesLen)++;
                }
            }
            chessboard->board[7][2] = '-';
            chessboard->board[7][3] = '-';
            chessboard->board[7][4] = 'K';
            chessboard->whiteKingPos = (BASIC_Coords){4, 7};
        }
    }
}

void BASIC_GenerateWhiteKingCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords possibleDirs[8] = {
        (BASIC_Coords){-1, -1}, (BASIC_Coords){-1, 0}, (BASIC_Coords){-1, 1}, (BASIC_Coords){0, -1},
        (BASIC_Coords){0, 1}, (BASIC_Coords){1, -1}, (BASIC_Coords){1, 0}, (BASIC_Coords){1, 1}
    };

    BASIC_Coords currentBoxPos;
    for (int i = 0; i < 8; i++) {
        currentBoxPos = (BASIC_Coords){piecePos.x + possibleDirs[i].x, piecePos.y + possibleDirs[i].y};
        if (currentBoxPos.x < 0 || currentBoxPos.x > 7 || currentBoxPos.y < 0 || currentBoxPos.y > 7 || !BASIC_IsSameColor(chessboard, currentBoxPos, 0)) continue;

        chessboard->whiteKingPos = currentBoxPos;
        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, 1, possibleMoves, possibleMovesLen);
        chessboard->whiteKingPos = piecePos;
    }
}

void BASIC_GenerateBlackKingMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords possibleDirs[8] = {
        (BASIC_Coords){-1, -1}, (BASIC_Coords){-1, 0}, (BASIC_Coords){-1, 1}, (BASIC_Coords){0, -1},
        (BASIC_Coords){0, 1}, (BASIC_Coords){1, -1}, (BASIC_Coords){1, 0}, (BASIC_Coords){1, 1}
    };

    BASIC_Coords currentBoxPos;
    for (int i = 0; i < 8; i++) {
        currentBoxPos = (BASIC_Coords){piecePos.x + possibleDirs[i].x, piecePos.y + possibleDirs[i].y};
        if (currentBoxPos.x < 0 || currentBoxPos.x > 7 || currentBoxPos.y < 0 || currentBoxPos.y > 7 || BASIC_IsSameColor(chessboard, currentBoxPos, 0)) continue;

        chessboard->blackKingPos = currentBoxPos;
        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, 0, possibleMoves, possibleMovesLen);
        chessboard->blackKingPos = piecePos;
    }

    if (!BASIC_IsBlackCheck(chessboard)) {
        if (chessboard->blackKingCastle && chessboard->board[0][5] == '-' && chessboard->board[0][6] == '-') {

            chessboard->board[0][5] = 'k';
            chessboard->board[0][4] = '-';
            chessboard->blackKingPos = (BASIC_Coords){5, 0};

            if (!BASIC_IsBlackCheck(chessboard)) {
                chessboard->board[0][6] = 'k';
                chessboard->board[0][5] = '-';
                chessboard->blackKingPos = (BASIC_Coords){6, 0};

                if (!BASIC_IsBlackCheck(chessboard)) {
                    possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){6, 0}};
                    (*possibleMovesLen)++;
                }
            }

            chessboard->board[0][4] = 'k';
            chessboard->board[0][5] = '-';
            chessboard->board[0][6] = '-';
            chessboard->blackKingPos = (BASIC_Coords){4, 0};
        }
        if (chessboard->blackQueenCastle && chessboard->board[0][3] == '-' && chessboard->board[0][2] == '-') {

            chessboard->board[0][3] = 'k';
            chessboard->board[0][4] = '-';
            chessboard->blackKingPos = (BASIC_Coords){3, 0};

            if (!BASIC_IsBlackCheck(chessboard)) {
                chessboard->board[0][2] = 'k';
                chessboard->board[0][3] = '-';
                chessboard->blackKingPos = (BASIC_Coords){2, 0};

                if (!BASIC_IsBlackCheck(chessboard)) {
                    possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, (BASIC_Coords){2, 0}};
                    (*possibleMovesLen)++;
                }
            }

            chessboard->board[0][4] = 'k';
            chessboard->board[0][3] = '-';
            chessboard->board[0][2] = '-';
            chessboard->blackKingPos = (BASIC_Coords){4, 0};
        }
    }
}

void BASIC_GenerateBlackKingCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    BASIC_Coords possibleDirs[8] = {
        (BASIC_Coords){-1, -1}, (BASIC_Coords){-1, 0}, (BASIC_Coords){-1, 1}, (BASIC_Coords){0, -1},
        (BASIC_Coords){0, 1}, (BASIC_Coords){1, -1}, (BASIC_Coords){1, 0}, (BASIC_Coords){1, 1}
    };

    BASIC_Coords currentBoxPos;
    for (int i = 0; i < 8; i++) {
        currentBoxPos = (BASIC_Coords){piecePos.x + possibleDirs[i].x, piecePos.y + possibleDirs[i].y};
        if (currentBoxPos.x < 0 || currentBoxPos.x > 7 || currentBoxPos.y < 0 || currentBoxPos.y > 7 || !BASIC_IsSameColor(chessboard, currentBoxPos, 1)) continue;

        chessboard->blackKingPos = currentBoxPos;
        BASIC_AddPossibleMove(chessboard, piecePos, currentBoxPos, 0, possibleMoves, possibleMovesLen);
        chessboard->blackKingPos = piecePos;
    }
}

void BASIC_AddPossibleMove(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords currentBoxPos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen)
{
    char buff;

    buff = chessboard->board[currentBoxPos.y][currentBoxPos.x];
    chessboard->board[currentBoxPos.y][currentBoxPos.x] = chessboard->board[piecePos.y][piecePos.x];
    chessboard->board[piecePos.y][piecePos.x] = '-';

    if ((isWhite) ? !BASIC_IsWhiteCheck(chessboard) : !BASIC_IsBlackCheck(chessboard)) {
        possibleMoves[*possibleMovesLen] = (BASIC_Move){piecePos, currentBoxPos};
        (*possibleMovesLen)++;
    }
    chessboard->board[piecePos.y][piecePos.x] = chessboard->board[currentBoxPos.y][currentBoxPos.x];
    chessboard->board[currentBoxPos.y][currentBoxPos.x] = buff;

}

int BASIC_IsWhiteCheck(BASIC_Chessboard* chessboard)
{
    BASIC_Coords currentBoxPos;

    for (int i = 1; i <= min(chessboard->whiteKingPos.x, chessboard->whiteKingPos.y); i++) { // left-up
        currentBoxPos = (BASIC_Coords){chessboard->whiteKingPos.x - i, chessboard->whiteKingPos.y - i};;
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'b') return 1;
        else if ((chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'p' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'k') && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= min(7 - chessboard->whiteKingPos.x, chessboard->whiteKingPos.y); i++) { // right-up
        currentBoxPos = (BASIC_Coords){chessboard->whiteKingPos.x + i, chessboard->whiteKingPos.y - i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'b') return 1;
        else if ((chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'p' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'k') && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= min(chessboard->whiteKingPos.x, 7 - chessboard->whiteKingPos.y); i++) { // left-down
        currentBoxPos = (BASIC_Coords){chessboard->whiteKingPos.x - i, chessboard->whiteKingPos.y + i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'b') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'k' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i < min(7 - chessboard->whiteKingPos.x, 7 - chessboard->whiteKingPos.y); i++) { // right-down
        currentBoxPos = (BASIC_Coords){chessboard->whiteKingPos.x + i, chessboard->whiteKingPos.y + i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'b') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'k' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= chessboard->whiteKingPos.y; i++) { // up
        currentBoxPos = (BASIC_Coords){chessboard->whiteKingPos.x, chessboard->whiteKingPos.y - i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'r') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'k' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= 7 - chessboard->whiteKingPos.y; i++) { // down
        currentBoxPos = (BASIC_Coords){chessboard->whiteKingPos.x, chessboard->whiteKingPos.y + i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'r') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'k' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= chessboard->whiteKingPos.x; i++) { // left
        currentBoxPos = (BASIC_Coords){chessboard->whiteKingPos.x - i, chessboard->whiteKingPos.y};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'r') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'k' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= 7 - chessboard->whiteKingPos.x; i++) { // right
        currentBoxPos = (BASIC_Coords){chessboard->whiteKingPos.x + i, chessboard->whiteKingPos.y};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'r') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'k' && i == 1) return 1;
        else break;
    }

    BASIC_Coords knightCheckPos[8] = {
        (BASIC_Coords){-2, -1}, (BASIC_Coords){-1, -2}, (BASIC_Coords){2, -1}, (BASIC_Coords){1, -2}, 
        (BASIC_Coords){-2, 1}, (BASIC_Coords){-1, 2}, (BASIC_Coords){2, 1}, (BASIC_Coords){1, 2}
    };

    for (int i = 0; i < 8; i++) { // knight
        currentBoxPos = (BASIC_Coords){chessboard->whiteKingPos.x + knightCheckPos[i].x, chessboard->whiteKingPos.y + knightCheckPos[i].y};
        if (currentBoxPos.x < 0 || currentBoxPos.x > 7 || currentBoxPos.y < 0 || currentBoxPos.y > 7) continue;
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'n') return 1;
    }

    return 0;
}

int BASIC_IsBlackCheck(BASIC_Chessboard* chessboard)
{
    BASIC_Coords currentBoxPos;

    for (int i = 1; i <= min(chessboard->blackKingPos.x, chessboard->blackKingPos.y); i++) { // left-up
        currentBoxPos = (BASIC_Coords){chessboard->blackKingPos.x - i, chessboard->blackKingPos.y - i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'Q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'B') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'K' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= min(7 - chessboard->blackKingPos.x, chessboard->blackKingPos.y); i++) { // right-up
        currentBoxPos = (BASIC_Coords){chessboard->blackKingPos.x + i, chessboard->blackKingPos.y - i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'Q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'B') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'K' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= min(chessboard->blackKingPos.x, 7 - chessboard->blackKingPos.y); i++) { // left-down
        currentBoxPos = (BASIC_Coords){chessboard->blackKingPos.x - i, chessboard->blackKingPos.y + i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'Q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'B') return 1;
        else if ((chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'P' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'K') && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= min(7 - chessboard->blackKingPos.x, 7 - chessboard->blackKingPos.y); i++) { // right-down
        currentBoxPos = (BASIC_Coords){chessboard->blackKingPos.x + i, chessboard->blackKingPos.y + i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'Q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'B') return 1;
        else if ((chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'P' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'K') && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= chessboard->blackKingPos.y; i++) { // up
        currentBoxPos = (BASIC_Coords){chessboard->blackKingPos.x, chessboard->blackKingPos.y - i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'Q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'R') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'K' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= 7 - chessboard->blackKingPos.y; i++) { // down
        currentBoxPos = (BASIC_Coords){chessboard->blackKingPos.x, chessboard->blackKingPos.y + i};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'Q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'R') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'K' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i <= chessboard->blackKingPos.x; i++) { // left
        currentBoxPos = (BASIC_Coords){chessboard->blackKingPos.x - i, chessboard->blackKingPos.y};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'Q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'R') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'K' && i == 1) return 1;
        else break;
    }

    for (int i = 1; i < 7 - chessboard->blackKingPos.x; i++) { // right
        currentBoxPos = (BASIC_Coords){chessboard->blackKingPos.x + i, chessboard->blackKingPos.y};
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == '-') continue;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'Q' || chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'R') return 1;
        else if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'K' && i == 1) return 1;
        else break;
    }

    BASIC_Coords knightCheckPos[8] = {
        (BASIC_Coords){-2, -1}, (BASIC_Coords){-1, -2}, (BASIC_Coords){2, -1}, (BASIC_Coords){1, -2}, 
        (BASIC_Coords){-2, 1}, (BASIC_Coords){-1, 2}, (BASIC_Coords){2, 1}, (BASIC_Coords){1, 2}
    };

    for (int i = 0; i < 8; i++) { // knight
        currentBoxPos = (BASIC_Coords){chessboard->blackKingPos.x + knightCheckPos[i].x, chessboard->blackKingPos.y + knightCheckPos[i].y};
        if (currentBoxPos.x < 0 || currentBoxPos.x > 7 || currentBoxPos.y < 0 || currentBoxPos.y > 7) continue;
        if (chessboard->board[currentBoxPos.y][currentBoxPos.x] == 'N') return 1;
    }

    return 0;
}

int BASIC_IsSameColor(BASIC_Chessboard* chessboard, BASIC_Coords pos, int IsWhite)
{
    if (IsWhite) {
        switch (chessboard->board[pos.y][pos.x]) {
            case 'P':
            case 'N':
            case 'B':
            case 'R':
            case 'Q':
            case 'K':
                return 1;
            default:
                return 0;
        }
    } else {
       switch (chessboard->board[pos.y][pos.x]) {
            case 'p':
            case 'n':
            case 'b':
            case 'r':
            case 'q':
            case 'k':
                return 1;
            default:
                return 0;
        }
    }
}