#ifndef ENUMPKG_H
#define ENUMPKG_H

#include <QObject>

namespace ChessEnums
{
    Q_NAMESPACE

    enum PlayerEnum
    {
        Player_White = 0,
        Player_Black = 1,
        Player_Count = 2
    };
    Q_ENUM_NS(PlayerEnum)

    enum TileStatusEnum
    {
        TileStatus_Empty = 0,
        TileStatus_NotEmpty = 1
    };

    enum PieceTypeEnum
    {
        PieceType_Pawn = 0,
        PieceType_Rook = 1,
        PieceType_Knight = 2,
        PieceType_Bishop = 3,
        PieceType_Queen = 4,
        PieceType_King = 5,
        PieceType_Count = 6
    };
    Q_ENUM_NS(PieceTypeEnum)

    enum PieceEnum
    {
        Piece_WhiteRook1 = 0,
        Piece_WhiteKnight1 = 1,
        Piece_WhiteBishop1 = 2,
        Piece_WhiteQueen = 3,
        Piece_WhiteKing = 4,
        Piece_WhiteBishop2 = 5,
        Piece_WhiteKnight2 = 6,
        Piece_WhiteRook2 = 7,
        Piece_WhitePawn1 = 8,
        Piece_WhitePawn2 = 9,
        Piece_WhitePawn3 = 10,
        Piece_WhitePawn4 = 11,
        Piece_WhitePawn5 = 12,
        Piece_WhitePawn6 = 13,
        Piece_WhitePawn7 = 14,
        Piece_WhitePawn8 = 15,
        Piece_BlackPawn1 = 16,
        Piece_BlackPawn2 = 17,
        Piece_BlackPawn3 = 18,
        Piece_BlackPawn4 = 19,
        Piece_BlackPawn5 = 20,
        Piece_BlackPawn6 = 21,
        Piece_BlackPawn7 = 22,
        Piece_BlackPawn8 = 23,
        Piece_BlackRook1 = 24,
        Piece_BlackKnight1 = 25,
        Piece_BlackBishop1 = 26,
        Piece_BlackQueen = 27,
        Piece_BlackKing = 28,
        Piece_BlackBishop2 = 29,
        Piece_BlackKnight2 = 30,
        Piece_BlackRook2 = 31,
        Piece_Count = 32
    };
    Q_ENUM_NS(PieceEnum)

    enum TileEnum
    {
        Tile_A1 = 0,
        Tile_B1 = 1,
        Tile_C1 = 2,
        Tile_D1 = 3,
        Tile_E1 = 4,
        Tile_F1 = 5,
        Tile_G1 = 6,
        Tile_H1 = 7,
        Tile_A2 = 8,
        Tile_B2 = 9,
        Tile_C2 = 10,
        Tile_D2 = 11,
        Tile_E2 = 12,
        Tile_F2 = 13,
        Tile_G2 = 14,
        Tile_H2 = 15,
        Tile_A3 = 16,
        Tile_B3 = 17,
        Tile_C3 = 18,
        Tile_D3 = 19,
        Tile_E3 = 20,
        Tile_F3 = 21,
        Tile_G3 = 22,
        Tile_H3 = 23,
        Tile_A4 = 24,
        Tile_B4 = 25,
        Tile_C4 = 26,
        Tile_D4 = 27,
        Tile_E4 = 28,
        Tile_F4 = 29,
        Tile_G4 = 30,
        Tile_H4 = 31,
        Tile_A5 = 32,
        Tile_B5 = 33,
        Tile_C5 = 34,
        Tile_D5 = 35,
        Tile_E5 = 36,
        Tile_F5 = 37,
        Tile_G5 = 38,
        Tile_H5 = 39,
        Tile_A6 = 40,
        Tile_B6 = 41,
        Tile_C6 = 42,
        Tile_D6 = 43,
        Tile_E6 = 44,
        Tile_F6 = 45,
        Tile_G6 = 46,
        Tile_H6 = 47,
        Tile_A7 = 48,
        Tile_B7 = 49,
        Tile_C7 = 50,
        Tile_D7 = 51,
        Tile_E7 = 52,
        Tile_F7 = 53,
        Tile_G7 = 54,
        Tile_H7 = 55,
        Tile_A8 = 56,
        Tile_B8 = 57,
        Tile_C8 = 58,
        Tile_D8 = 59,
        Tile_E8 = 60,
        Tile_F8 = 61,
        Tile_G8 = 62,
        Tile_H8 = 63,
        Tile_Count = 64
    };
    Q_ENUM_NS(TileEnum)
}

#endif // !ENUMPKG_H
