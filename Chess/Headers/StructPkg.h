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
    PieceStc Piece;
};

struct TableStc
{
    SquareStc Square[File_Count * Rank_Count];
};

#endif