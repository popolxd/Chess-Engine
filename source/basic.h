#ifndef BASIC_H
#define BASIC_H

typedef struct {
    int x, y;
} BASIC_Coords;

typedef struct {
    BASIC_Coords startingPos;
    BASIC_Coords targetPos;
} BASIC_Move;

typedef struct {
    char board[8][8];
    int whiteKingCastle, whiteQueenCastle, blackKingCastle, blackQueenCastle;
    BASIC_Coords enPassantSquare;
    BASIC_Coords whiteKingPos;
    BASIC_Coords blackKingPos;

    int whiteToMove;

    // int isSelectedPiece;
    // BASIC_Coords selectedPiecePos;
    // BASIC_Coords possibleMoves[27];
    // int possibleMovesLen;

} BASIC_Chessboard;

void BASIC_MovePiece(BASIC_Chessboard* chessboard, BASIC_Coords startingPos, BASIC_Coords targetPos);

void BASIC_GeneratePossibleMovesForPiece(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GeneratePossibleCapturesForPiece(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);

void BASIC_GenerateBishopMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateRookMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateKnightMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateWhitePawnMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateBlackPawnMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateWhiteKingMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateBlackKingMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);

void BASIC_GenerateBishopCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateRookCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateKnightCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateWhitePawnCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateBlackPawnCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateWhiteKingCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);
void BASIC_GenerateBlackKingCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords possibleMoves[27], int* possibleMovesLen);

int BASIC_IsWhiteCheck(BASIC_Chessboard* chessboard);
int BASIC_IsBlackCheck(BASIC_Chessboard* chessboard);

void BASIC_AddPossibleMove(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords currentBoxPos, int isWhite, BASIC_Coords possibleMoves[27], int* possibleMovesLen);

int BASIC_IsSameColor(BASIC_Chessboard* chessboard, BASIC_Coords pos, int isWhite);

#endif