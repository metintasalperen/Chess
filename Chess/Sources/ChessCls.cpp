#include "Headers/ChessCls.h"

// for memset
#include <string.h>

ChessCls::ChessCls()
{
	Initialize();
}

void ChessCls::Initialize()
{
    Turn = Player_White;
    TurnCount = 0;

    memset(&Table, 0, sizeof(Table));
    for (int i = 0; i < File_Count; i++)
    {
        for (int j = 0; j < Rank_Count; j++)
        {
            unsigned int index = CalculateIndex(static_cast<FileEnum>(i), static_cast<RankEnum>(j));

            if (index < 16)
            {
                Table.Square[index].State = SquareState_Occupied;
                Table.Square[index].Piece.Owner = Player_Black;

                if (index >= 8)
                {
                    Table.Square[index].Piece.Name = Piece_Pawn;
                }
                else if (index == 0 || index == 7)
                {
                    Table.Square[index].Piece.Name = Piece_Rook;
                }
                else if (index == 1 || index == 6)
                {
                    Table.Square[index].Piece.Name = Piece_Knight;
                }
                else if (index == 2 || index == 5)
                {
                    Table.Square[index].Piece.Name = Piece_Bishop;
                }
                else if (index == 3)
                {
                    Table.Square[index].Piece.Name = Piece_Queen;
                }
                else if (index == 4)
                {
                    Table.Square[index].Piece.Name = Piece_King;
                }
            }
            else if (index >= 48)
            {
                Table.Square[index].State = SquareState_Occupied;
                Table.Square[index].Piece.Owner = Player_White;

                if (index < 56)
                {
                    Table.Square[index].Piece.Name = Piece_Pawn;
                }
                else if (index == 56 || index == 63)
                {
                    Table.Square[index].Piece.Name = Piece_Rook;
                }
                else if (index == 57 || index == 62)
                {
                    Table.Square[index].Piece.Name = Piece_Knight;
                }
                else if (index == 58 || index == 61)
                {
                    Table.Square[index].Piece.Name = Piece_Bishop;
                }
                else if (index == 59)
                {
                    Table.Square[index].Piece.Name = Piece_Queen;
                }
                else if (index == 60)
                {
                    Table.Square[index].Piece.Name = Piece_King;
                }
            }
            else
            {
                Table.Square[index].State = SquareState_Empty;
            }
        }
    }
}

uint32_t ChessCls::CalculateIndex(uint32_t file, uint32_t rank)
{
    uint32_t index = 8 * (7 - rank) + file;
    return index;
}

uint32_t ChessCls::CalculateIndex(const FileEnum& file, const RankEnum& rank)
{
    uint32_t index = 8 * (7 - static_cast<uint32_t>(rank)) + static_cast<uint32_t>(file);
    return index;
}

bool ChessCls::ProcessUserInput(const MoveStc& from, const MoveStc& to)
{
    bool result = CheckMoveValidity(from, to);

    if (result == true)
    {
        Table.Square[CalculateIndex(to.File, to.Rank)].State = SquareState_Occupied;
        Table.Square[CalculateIndex(to.File, to.Rank)].Piece.Name = Table.Square[CalculateIndex(from.File, from.Rank)].Piece.Name;
        Table.Square[CalculateIndex(to.File, to.Rank)].Piece.Owner = Table.Square[CalculateIndex(from.File, from.Rank)].Piece.Owner;

        Table.Square[CalculateIndex(from.File, from.Rank)].State = SquareState_Empty;

        SwitchTurn();
    }

    return result;
}

void ChessCls::UpdateTableState(TableStc*& table)
{
    table = &Table;
}

PlayerEnum ChessCls::GetTurn()
{
    return Turn;
}

UiChessIfc* ChessCls::GetItsUiChessIfc()
{
    return this;
}

void ChessCls::SwitchTurn()
{
    if (Turn == Player_White)
    {
        Turn = Player_Black;
    }
    else
    {
        Turn = Player_White;
    }
}

bool ChessCls::CheckMoveValidity(const MoveStc& from, const MoveStc& to)
{
    uint32_t fromIndex = CalculateIndex(from.File, from.Rank);
    uint32_t toIndex   = CalculateIndex(to.File, to.Rank);

    // If ANY of the following conditions are satisfied, return false
    // A. Player tries to move a piece that does not belong to him
    // B. Player selects and empty location
    // C. Player tries to capture his own piece

    if ((Table.Square[fromIndex].State == SquareState_Occupied) &&
        (Table.Square[fromIndex].Piece.Owner != Turn))
    {
        return false;
    }
    if (Table.Square[fromIndex].State == SquareState_Empty)
    {
        return false;
    }
    if ((Table.Square[toIndex].State == SquareState_Occupied) &&
        (Table.Square[toIndex].Piece.Owner == Turn))
    {
        return false;
    }

    bool result = false;
    switch (Table.Square[fromIndex].Piece.Name)
    {
        case Piece_Pawn:
        {
            result = CheckPawnMoveValidity(from, to);
            break;
        }
        case Piece_Rook:
        {
            result = CheckRookMoveValidity(from, to);
            break;
        }
        case Piece_Knight:
        {
            result = CheckKnightMoveValidity(from, to);
            break;
        }
        case Piece_Bishop:
        {
            result = CheckBishopMoveValidity(from, to);
            break;
        }
        case Piece_Queen:
        {
            result = CheckQueenMoveValidity(from, to);
            break;
        }
        case Piece_King:
        {
            break;
        }
        default:
        {
            result = false;
            break;
        }
    }

    return result;
}

bool ChessCls::CheckPawnMoveValidity(const MoveStc& from, const MoveStc& to)
{
    uint32_t fromIndex = CalculateIndex(from.File, from.Rank);
    uint32_t toIndex   = CalculateIndex(to.File, to.Rank);

    if (Table.Square[fromIndex].Piece.Owner == Player_White)
    {
        if (Table.Square[toIndex].State == SquareState_Empty)
        {
            // White piece can only move forward but not sideways
            // Therefore, if File changes, then move is invalid
            if (from.File != to.File)
            {
                return false;
            }

            if (from.Rank == Rank_2)
            {
                // Pawn moves 1 tile forward. This move is valid, return true
                if (to.Rank == Rank_3)
                {
                    return true;
                }
                else if (to.Rank == Rank_4)
                {
                    // Pawn moves 2 tile forward. 1 tile forward is empty, so this move is valid
                    if (Table.Square[CalculateIndex(to.File, Rank_3)].State == SquareState_Empty)
                    {
                        return true;
                    }
                    // Pawn moves 2 tile forward but 1 tile forward is occupied, so this move is invalid.
                    else
                    {
                        return false;
                    }
                }
                // Pawn moves more than 2 tiles forward. This move is invalid
                else
                {
                    return false;
                }
            } // Rank_2
            else
            {
                if (to.Rank == from.Rank + 1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            } // NOT Rank_2
        } // SquareState_Empty
        else if (Table.Square[toIndex].State == SquareState_Occupied)
        {
            // Piece does not move 1 tile forward. This move is invalid
            if (to.Rank != from.Rank + 1)
            {
                return false;
            }

            if (from.File == File_A)
            {
                if (to.File == File_B)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (from.File == File_H)
            {
                if (to.File == File_G)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if ((from.File == to.File + 1) ||
                    (from.File == to.File - 1))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        } // SquareState_Occupied
    } // Player_White
    else if (Table.Square[fromIndex].Piece.Owner == Player_Black)
    {
        if (Table.Square[toIndex].State == SquareState_Empty)
        {
            // Black piece can only move backward but not sideways
            // Therefore, if File changes, then move is invalid
            if (from.File != to.File)
            {
                return false;
            }

            // If rank is 7, then pawn can either move 1 tile backward or 2 tile backward
            // Else, pawn can only move 1 tile backward
            if (from.Rank == Rank_7)
            {
                // Pawn moves 1 tile backward. This move is valid, return true
                if (to.Rank == Rank_6)
                {
                    return true;
                }
                else if (to.Rank == Rank_5)
                {
                    // Pawn moves 2 tile backward. 1 tile backward is empty, so this move is valid
                    if (Table.Square[CalculateIndex(to.File, Rank_6)].State == SquareState_Empty)
                    {
                        return true;
                    }
                    // Pawn moves 2 tile backward but 1 tile backward is occupied, so this move is invalid.
                    else
                    {
                        return false;
                    }
                }
                // Pawn moves more than 2 tiles backward. This move is invalid
                else
                {
                    return false;
                }
            }
            // If rank is not 7, then pawn can only move 1 tile forward
            else
            {
                if (to.Rank == from.Rank - 1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        else if (Table.Square[toIndex].State == SquareState_Occupied)
        {
            // Piece does not move 1 tile backward. This move is invalid
            if (to.Rank != from.Rank - 1)
            {
                return false;
            }

            if (from.File == File_A)
            {
                if (to.File == File_B)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (from.File == File_H)
            {
                if (to.File == File_G)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if ((from.File == to.File + 1) ||
                    (from.File == to.File - 1))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    } // Player_Black

    // Defensive, should not reach here
    return false;
}

bool ChessCls::CheckRookMoveValidity(const MoveStc& from, const MoveStc& to)
{
    // Forward / Backward move
    if ((from.File == to.File) && (from.Rank != to.Rank))
    {
        // Forward move
        if (to.Rank > from.Rank)
        {
            uint32_t diff = to.Rank - from.Rank;

            for (uint32_t i = 1; i < diff; i++)
            {
                uint32_t index = CalculateIndex(static_cast<uint32_t>(from.File), from.Rank + i);
                if (Table.Square[index].State == SquareState_Occupied)
                {
                    return false;
                }
            }

            return true;
        }
        // Backward move
        else
        {
            uint32_t diff = from.Rank - to.Rank;

            for (uint32_t i = 1; i < diff; i++)
            {
                uint32_t index = CalculateIndex(static_cast<uint32_t>(from.File), from.Rank - i);
                if (Table.Square[index].State == SquareState_Occupied)
                {
                    return false;
                }
            }

            return true;
        }
    }
    else if ((from.File != to.File) && (from.Rank == to.Rank))
    {
        // Right move
        if (to.File > from.File)
        {
            uint32_t diff = to.File - from.File;

            for (uint32_t i = 1; i < diff; i++)
            {
                uint32_t index = CalculateIndex(static_cast<FileEnum>(from.File + i), from.Rank);
                if (Table.Square[index].State == SquareState_Occupied)
                {
                    return false;
                }
            }

            return true;
        }
        // Left move
        else
        {
            uint32_t diff = from.File - to.File;

            for (uint32_t i = 1; i < diff; i++)
            {
                uint32_t index = CalculateIndex(static_cast<FileEnum>(from.File - i), from.Rank);
                if (Table.Square[index].State == SquareState_Occupied)
                {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}

bool ChessCls::CheckKnightMoveValidity(const MoveStc& from, const MoveStc& to)
{
    if (((to.Rank == from.Rank + 2) && (to.File == from.File + 1)) ||
        ((to.Rank == from.Rank + 1) && (to.File == from.File + 2)) ||
        ((to.Rank == from.Rank + 2) && (to.File == from.File - 1)) ||
        ((to.Rank == from.Rank + 1) && (to.File == from.File - 2)) ||
        ((to.Rank == from.Rank - 2) && (to.File == from.File + 1)) ||
        ((to.Rank == from.Rank - 1) && (to.File == from.File + 2)) ||
        ((to.Rank == from.Rank - 2) && (to.File == from.File - 1)) ||
        ((to.Rank == from.Rank - 1) && (to.File == from.File - 2)))
    {
        return true;
    }

    return false;
}

bool ChessCls::CheckBishopMoveValidity(const MoveStc& from, const MoveStc& to)
{
    uint32_t fileDiff = 0;
    uint32_t rankDiff = 0;

    // When bishop moves, both rank and file should change
    // If either of them does not change, move is invalid
    if ((from.Rank == to.Rank) ||
        (from.File == to.File))
    {
        return false;
    }

    // Since bishop moves diagonally, file change and rank change should be equal
    // If it is not equal, then move is not diagonal and invalid
    if (from.File > to.File)
    {
        fileDiff = from.File - to.File;
    }
    else
    {
        fileDiff = to.File - from.File;
    }

    if (from.Rank > to.Rank)
    {
        rankDiff = from.Rank - to.Rank;
    }
    else
    {
        rankDiff = to.Rank - from.Rank;
    }

    if (fileDiff != rankDiff)
    {
        return false;
    }

    uint32_t file = static_cast<uint32_t>(from.File);
    uint32_t rank = static_cast<uint32_t>(from.Rank);

    while (file != to.File)
    {
        // Bottom left movement
        if ((from.File > to.File) && (from.Rank > to.Rank))
        {
            file = file - 1;
            rank = rank - 1;

        }
        // Top left movement
        else if ((from.File > to.File) && (from.Rank < to.Rank))
        {
            file = file - 1;
            rank = rank + 1;
        }
        // Bottom right movement
        else if ((from.File < to.File) && (from.Rank > to.Rank))
        {
            file = file + 1;
            rank = rank - 1;
        }
        // Top right movement
        else if ((from.File < to.File) && (from.Rank < to.Rank))
        {
            file = file + 1;
            rank = rank + 1;
        }

        if (file == to.File)
        {
            return true;
        }

        uint32_t index = CalculateIndex(file, rank);

        if (Table.Square[index].State == SquareState_Occupied)
        {
            return false;
        }
    }

    return true;
}

bool ChessCls::CheckQueenMoveValidity(const MoveStc& from, const MoveStc& to)
{
    uint32_t fileDiff = 0;
    uint32_t rankDiff = 0;
    uint32_t index = 0;

    // Forward/Backward movement
    if ((from.File == to.File) && (from.Rank != to.Rank))
    {
        if (to.Rank > from.Rank)
        {
            rankDiff = to.Rank - from.Rank;

            for (uint32_t i = 1; i < rankDiff; i++)
            {
                index = CalculateIndex(static_cast<uint32_t>(from.File), from.Rank + i);

                if (Table.Square[index].State == SquareState_Occupied)
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            rankDiff = from.Rank - to.Rank;

            for (uint32_t i = 1; i < rankDiff; i++)
            {
                index = CalculateIndex(static_cast<uint32_t>(from.File), from.Rank - i);

                if (Table.Square[index].State == SquareState_Occupied)
                {
                    return false;
                }
            }

            return true;
        }
    }
    // Sideways movement
    else if ((from.File != to.File) && (from.Rank == to.Rank))
    {
        if (to.File > from.File)
        {
            fileDiff = to.File - from.File;

            for (uint32_t i = 1; i < fileDiff; i++)
            {
                uint32_t index = CalculateIndex(from.File + i, static_cast<uint32_t>(from.Rank));

                if (Table.Square[index].State == SquareState_Occupied)
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            fileDiff = from.File - to.File;

            for (uint32_t i = 1; i < fileDiff; i++)
            {
                uint32_t index = CalculateIndex(from.File - i, static_cast<uint32_t>(from.Rank));

                if (Table.Square[index].State == SquareState_Occupied)
                {
                    return false;
                }
            }

            return true;
        }
    }
    // Diagonal movement
    else if ((from.File != to.File) && (from.Rank != to.Rank))
    {
        if (to.Rank > from.Rank)
        {
            rankDiff = to.Rank - from.Rank;
        }
        else
        {
            rankDiff = from.Rank - to.Rank;
        }

        if (to.File > from.File)
        {
            fileDiff = to.File - from.File;
        }
        else
        {
            fileDiff = from.File - to.File;
        }

        // File and rank difference are not equal
        // This movement is not diagonal
        if (fileDiff != rankDiff)
        {
            return false;
        }

        uint32_t file = static_cast<uint32_t>(from.File);
        uint32_t rank = static_cast<uint32_t>(from.Rank);

        while (file != to.File)
        {
            // Bottom left movement
            if ((from.File > to.File) && (from.Rank > to.Rank))
            {
                file = file - 1;
                rank = rank - 1;

            }
            // Top left movement
            else if ((from.File > to.File) && (from.Rank < to.Rank))
            {
                file = file - 1;
                rank = rank + 1;
            }
            // Bottom right movement
            else if ((from.File < to.File) && (from.Rank > to.Rank))
            {
                file = file + 1;
                rank = rank - 1;
            }
            // Top right movement
            else if ((from.File < to.File) && (from.Rank < to.Rank))
            {
                file = file + 1;
                rank = rank + 1;
            }

            if (file == to.File)
            {
                return true;
            }

            uint32_t index = CalculateIndex(file, rank);

            if (Table.Square[index].State == SquareState_Occupied)
            {
                return false;
            }
        }

        return true;
    }

    return false;
}
