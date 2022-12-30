#ifndef STRUCTPKG_H
#define STRUCTPKG

#include "EnumPkg.h"
using namespace ChessEnums;

struct PieceStc
{
    PieceTypeEnum pieceType;
    PieceEnum pieceId;
    PlayerEnum player;
};

struct TileStc
{
    TileStatusEnum tileStatus;
    PieceStc piece;
};

#endif // !STRUCTPKG_H
