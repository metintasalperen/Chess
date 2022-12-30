#include "ChessLogicCls.h"
#define DEBUG

#ifdef DEBUG
#include <QDebug>
#endif // DEBUG

ChessLogicCls::ChessLogicCls()
{
	memset(&TileArr[0], 0, sizeof(TileStc) * Tile_Count);

	for (int i = 0; i < Tile_Count; i++)
	{
		if (i <= Tile_H2)
		{
			TileArr[i].tileStatus = TileStatus_NotEmpty;
			TileArr[i].piece.player = Player_White;
			TileArr[i].piece.pieceId = static_cast<PieceEnum>(i);

			if (i >= Tile_A2)
			{
				TileArr[i].piece.pieceType = PieceType_Pawn;
			}
            else if ((i == Tile_A1) || (i == Tile_H1))
            {
                TileArr[i].piece.pieceType = PieceType_Rook;
            }
            else if ((i == Tile_B1) || (i == Tile_G1))
            {
                TileArr[i].piece.pieceType = PieceType_Knight;
            }
            else if ((i == Tile_C1) || (i == Tile_F1))
            {
                TileArr[i].piece.pieceType = PieceType_Bishop;
            }
            else if (i == Tile_D1)
            {
                TileArr[i].piece.pieceType = PieceType_Queen;
            }
            else if (i == Tile_E1)
            {
                TileArr[i].piece.pieceType = PieceType_King;
            }
		}
        else if (i >= Tile_A7)
        {
            TileArr[i].tileStatus = TileStatus_NotEmpty;
            TileArr[i].piece.player = Player_Black;
            TileArr[i].piece.pieceId = static_cast<PieceEnum>(i - 32);

            if (i <= Tile_H7)
            {
                TileArr[i].piece.pieceType = PieceType_Pawn;
            }
            else if ((i == Tile_A8) || (i == Tile_H8))
            {
                TileArr[i].piece.pieceType = PieceType_Rook;
            }
            else if ((i == Tile_B8) || (i == Tile_G8))
            {
                TileArr[i].piece.pieceType = PieceType_Knight;
            }
            else if ((i == Tile_C8) || (i == Tile_F8))
            {
                TileArr[i].piece.pieceType = PieceType_Bishop;
            }
            else if (i == Tile_D8)
            {
                TileArr[i].piece.pieceType = PieceType_Queen;
            }
            else if (i == Tile_E8)
            {
                TileArr[i].piece.pieceType = PieceType_King;
            }
        }
        else
        {
            TileArr[i].tileStatus = TileStatus_Empty;
        }
	}
}

int ChessLogicCls::CalculateIndex(int row, int col)
{
    int index = (8 * row) + col;
    return index;
}

void ChessLogicCls::CalculatePossibleMoves(TileEnum index, TileEnum* posMoveIndex)
{
    if (TileArr[index].tileStatus == TileStatus_Empty)
    {
#ifdef DEBUG
        qDebug() << "Empty tile is selected!";
#endif // DEBUG

        posMoveIndex[0] = Tile_Count;
        return;
    }

    switch (TileArr[index].piece.pieceType)
    {
        case PieceType_Pawn:
        {
        }
        case PieceType_Rook:
        {
        }
        case PieceType_Knight:
        {
        }
        case PieceType_Bishop:
        {
        }
        case PieceType_Queen:
        {
        }
        case PieceType_King:
        {
        }
        default:
        {
        }
    }
}
