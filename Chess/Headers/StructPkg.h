#ifndef STRUCTPKG_H
#define STRUCTPKG_H

#include "EnumPkg.h"

struct MoveStc
{
    FileEnum File;
    RankEnum Rank;
};

struct PieceStc
{
    PieceEnum Name;
    PlayerEnum Owner;
};

struct SquareStc
{
    SquareStateEnum State;

    // Data in Piece is valid only if State is SquareState_Occupied
    PieceStc Piece;
    
    // Data in IsRookMoved is valid only if Piece.Name is Piece_Rook
    bool IsRookMoved;
};

struct TableStc
{
    SquareStc Square[File_Count * Rank_Count];
};

#endif