#ifndef ENUMPKG_H
#define ENUMPKG_H

enum FileEnum
{
    File_A = 0,
    File_B,
    File_C,
    File_D,
    File_E,
    File_F,
    File_G,
    File_H,
    File_Count
};

enum RankEnum
{
    Rank_1 = 0,
    Rank_2,
    Rank_3,
    Rank_4,
    Rank_5,
    Rank_6,
    Rank_7,
    Rank_8,
    Rank_Count
};

enum SquareStateEnum
{
    SquareState_Empty = 0,
    SquareState_Occupied
};

enum PlayerEnum
{
    Player_White = 0,
    Player_Black,
    Player_Count
};

enum PieceEnum
{
    Piece_Pawn = 0,
    Piece_Rook,
    Piece_Knight,
    Piece_Bishop,
    Piece_Queen,
    Piece_King
};

enum GameStateEnum
{
    GameState_Ongoing = 0,
    GameState_WhiteWon,
    GameState_BlackWon,
    GameState_Stalemate
};

#endif