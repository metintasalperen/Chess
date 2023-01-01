#ifndef CHESSLOGICCLS_H
#define CHESSLOGICCLS_H

#include "StructPkg.h"

class ChessLogicCls
{
public:
    // Attributes
    // 8x8 chess board state
    TileStc TileArr[Tile_Count];
    // Player turn
    PlayerEnum PlayerTurn;
    // Indicates whether a piece is clicked to move
    PieceClickedEnum PieceClicked;

    // Methods
    // Default constructor
    ChessLogicCls();

    // Maps 2d chess coordinates to 1d array
    int CalculateIndex(int row, int col);

    // returns the id of piece in given tile index
    PieceEnum GetPieceId(TileEnum index);

    // Getters
    PlayerEnum GetPlayerTurn();
    PieceClickedEnum GetPieceClicked();

    // Calculates possible moves of piece in given tile
    // 
    // Parameters:
    // tile - in
    // posMoveList - out
    void CalculatePossibleMoves(TileEnum index, TileEnum* posMoveList);

private:
    void CalculatePossiblePawnMoves(TileEnum index, TileEnum* posMoveList);
    void CalculatePossibleRookMoves(TileEnum index, TileEnum* posMoveList);
    void CalculatePossibleKnightMoves(TileEnum index, TileEnum* posMoveList);
    void CalculatePossibleBishopMoves(TileEnum index, TileEnum* posMoveList);
    void CalculatePossibleQueenMoves(TileEnum index, TileEnum* posMoveList);
    void CalculatePossibleKingMoves(TileEnum index, TileEnum* posMoveList);
};

#endif // !CHESSLOGICCLS_H
