#ifndef BASIC_H
#define BASIC_H

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
 
typedef struct {
    int x, y;
} BASIC_Coords;

typedef struct {
    BASIC_Coords startingPos;
    BASIC_Coords targetPos;
    
} BASIC_Move;

typedef struct {
    char type;
    BASIC_Coords pos;
} BASIC_Piece;

typedef struct {
    char board[8][8];
    int whiteKingCastle, whiteQueenCastle, blackKingCastle, blackQueenCastle;
    BASIC_Coords enPassantSquare;
    BASIC_Coords whiteKingPos;
    BASIC_Coords blackKingPos;

    // BASIC_Piece pieces[32];
    // int piecesLen;

    int whiteToMove;
} BASIC_Chessboard;

void BASIC_MovePiece(BASIC_Chessboard* chessboard, BASIC_Coords startingPos, BASIC_Coords targetPos);

void BASIC_GenerateAllPossibleMoves(BASIC_Chessboard* chessboard, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateAllPossibleCaptures(BASIC_Chessboard* chessboard, BASIC_Move* possibleCaptures, int* possibleCapturesLen);

void BASIC_GeneratePossibleMovesForPiece(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GeneratePossibleCapturesForPiece(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);

void BASIC_GenerateBishopMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateRookMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateKnightMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateWhitePawnMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateBlackPawnMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateWhiteKingMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateBlackKingMoves(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);

void BASIC_GenerateBishopCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateRookCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateKnightCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateWhitePawnCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateBlackPawnCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateWhiteKingCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);
void BASIC_GenerateBlackKingCaptures(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Move* possibleMoves, int* possibleMovesLen);

int BASIC_IsWhiteCheck(BASIC_Chessboard* chessboard);
int BASIC_IsBlackCheck(BASIC_Chessboard* chessboard);

void BASIC_AddPossibleMove(BASIC_Chessboard* chessboard, BASIC_Coords piecePos, BASIC_Coords currentBoxPos, int isWhite, BASIC_Move* possibleMoves, int* possibleMovesLen);

int BASIC_IsSameColor(BASIC_Chessboard* chessboard, BASIC_Coords pos, int isWhite);

#endif