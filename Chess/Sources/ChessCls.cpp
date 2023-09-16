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
