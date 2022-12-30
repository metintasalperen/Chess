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
};

#endif // !CHESSLOGICCLS_H
