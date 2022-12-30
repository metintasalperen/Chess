#ifndef CHESSLOGICCLS_H
#define CHESSLOGICCLS_H

#include "StructPkg.h"

class ChessLogicCls
{
public:
    // Attributes
    TileStc TileArr[Tile_Count];

    // Methods
    // Default constructor
    ChessLogicCls();

    // Maps 2d chess coordinates to 1d array
    int CalculateIndex(int row, int col);

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
