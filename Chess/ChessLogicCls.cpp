#include "ChessLogicCls.h"
#define DEBUG

#ifdef DEBUG
#include <QDebug>
#endif // DEBUG

ChessLogicCls::ChessLogicCls()
{
    PlayerTurn = Player_White;
    PieceClicked = PieceClicked_NotClicked;

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

PieceEnum ChessLogicCls::GetPieceId(TileEnum index)
{
    if (TileArr[index].tileStatus == TileStatus_NotEmpty)
    {
        return TileArr[index].piece.pieceId;
    }
    else
    {
        return Piece_Count;
    }
}

PlayerEnum ChessLogicCls::GetPlayerTurn()
{
    return PlayerTurn;
}

PieceClickedEnum ChessLogicCls::GetPieceClicked()
{
    return PieceClicked;
}

void ChessLogicCls::TogglePieceClicked()
{
    if (PieceClicked == PieceClicked_Clicked)
    {
        PieceClicked = PieceClicked_NotClicked;
    }
    else if (PieceClicked == PieceClicked_NotClicked)
    {
        PieceClicked = PieceClicked_Clicked;
    }
}

void ChessLogicCls::CalculatePossibleMoves(TileEnum index, TileEnum* posMoveIndex)
{
    // return no possible moves if clicked tile is empty
    if (TileArr[index].tileStatus == TileStatus_Empty)
    {
#ifdef DEBUG
        qDebug() << "Empty tile is selected!";
#endif // DEBUG

        posMoveIndex[0] = Tile_Count;
        return;
    }
    else if (((TileArr[index].piece.player == Player_White) &&
              (PlayerTurn == Player_Black)) ||
             ((TileArr[index].piece.player == Player_Black) &&
              (PlayerTurn == Player_White)))
    {
#ifdef DEBUG
        qDebug() << "Wrong player move!";
#endif // DEBUG

        posMoveIndex[0] = Tile_Count;
        return;
    }

    switch (TileArr[index].piece.pieceType)
    {
        case PieceType_Pawn:
        {
            CalculatePossiblePawnMoves(index, posMoveIndex);
            //TogglePieceClicked();
            break;
        }
        case PieceType_Rook:
        {
            break;
        }
        case PieceType_Knight:
        {
            break;
        }
        case PieceType_Bishop:
        {
            break;
        }
        case PieceType_Queen:
        {
            break;
        }
        case PieceType_King:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

void ChessLogicCls::CalculatePossiblePawnMoves(TileEnum index, TileEnum* posMoveList)
{
    // TODO: Implement "en passant" move
    int posMoveListIndex = 0;

    if (TileArr[index].piece.player == Player_White)
    {
        // Note: These assignments could be a source of bug if index + val is greater than Tile_Count
        // Investigate
        TileEnum oneForwardMoveWhite = static_cast<TileEnum>(index + 8);
        TileEnum twoForwardMoveWhite = static_cast<TileEnum>(index + 16);
        TileEnum leftCaptureMoveWhite = static_cast<TileEnum>(index + 7);
        TileEnum rightCaptureMoveWhite = static_cast<TileEnum>(index + 9);

        // Calculation of non-capture moves
        // Pawn has not move yet, it can move two tiles forward
        if ((index >= Tile_A2) &&
            (index <= Tile_H2))
        {
            // One tile forward is occupied, nowhere to move
            if (TileArr[oneForwardMoveWhite].tileStatus == TileStatus_NotEmpty)
            {
                posMoveList[0] = Tile_Count;
            }
            // One tile forward is free, two file forward is occupied
            // Add index of one tile forward to list
            else if ((TileArr[oneForwardMoveWhite].tileStatus == TileStatus_Empty) &&
                     (TileArr[twoForwardMoveWhite].tileStatus == TileStatus_NotEmpty))
            {
                posMoveList[0] = oneForwardMoveWhite;
                posMoveList[1] = Tile_Count;
                posMoveListIndex = 1;
            }
            // One and two tiles forward are free
            // Add indexes of both tiles to list
            else if ((TileArr[oneForwardMoveWhite].tileStatus == TileStatus_Empty) &&
                     (TileArr[twoForwardMoveWhite].tileStatus == TileStatus_Empty))
            {
                posMoveList[0] = oneForwardMoveWhite;
                posMoveList[1] = twoForwardMoveWhite;
                posMoveList[2] = Tile_Count;
                posMoveListIndex = 2;
            }
        }
        // Pawn moved at least one, it can only move one tile forward
        else if ((index >= Tile_A3) &&
                 (index <= Tile_H7))
        {
            // One tile forward is occupied, nowhere to move
            if (TileArr[oneForwardMoveWhite].tileStatus == TileStatus_NotEmpty)
            {
                posMoveList[0] = Tile_Count;
            }
            // One tile forward is free, add index of one tile forward to list
            else if (TileArr[oneForwardMoveWhite].tileStatus == TileStatus_Empty)
            {
                posMoveList[0] = oneForwardMoveWhite;
                posMoveList[1] = Tile_Count;
                posMoveListIndex = 1;
            }
        }

        // Calculation of capture moves
        // Pawn is in left corner, can only capture through right
        if ((index == Tile_A2) ||
            (index == Tile_A3) ||
            (index == Tile_A4) ||
            (index == Tile_A5) ||
            (index == Tile_A6) ||
            (index == Tile_A7))
        {
            if ((TileArr[rightCaptureMoveWhite].tileStatus == TileStatus_NotEmpty) &&
                (TileArr[rightCaptureMoveWhite].piece.player == Player_Black))
            {
                posMoveList[posMoveListIndex] = rightCaptureMoveWhite;
                posMoveList[posMoveListIndex + 1] = Tile_Count;
            }
        }
        // Pawn is in right corner, can only capture through left
        else if ((index == Tile_H2) ||
                 (index == Tile_H3) ||
                 (index == Tile_H4) ||
                 (index == Tile_H5) ||
                 (index == Tile_H6) ||
                 (index == Tile_H7))
        {
            if ((TileArr[leftCaptureMoveWhite].tileStatus == TileStatus_NotEmpty) &&
                (TileArr[leftCaptureMoveWhite].piece.player == Player_Black))
            {
                posMoveList[posMoveListIndex] = leftCaptureMoveWhite;
                posMoveList[posMoveListIndex + 1] = Tile_Count;
            }
        }
        // Pawn is in middle, can capture both through left and right
        else if (((index > Tile_A2) && (index < Tile_H2)) ||
                 ((index > Tile_A3) && (index < Tile_H3)) ||
                 ((index > Tile_A4) && (index < Tile_H4)) ||
                 ((index > Tile_A5) && (index < Tile_H5)) ||
                 ((index > Tile_A6) && (index < Tile_H6)) ||
                 ((index > Tile_A7) && (index < Tile_H7)))
        {
            if ((TileArr[leftCaptureMoveWhite].tileStatus == TileStatus_NotEmpty) &&
                (TileArr[leftCaptureMoveWhite].piece.player == Player_Black))
            {
                posMoveList[posMoveListIndex] = leftCaptureMoveWhite;
                posMoveListIndex = posMoveListIndex + 1;
            }
            if ((TileArr[rightCaptureMoveWhite].tileStatus == TileStatus_NotEmpty) &&
                (TileArr[rightCaptureMoveWhite].piece.player == Player_Black))
            {
                posMoveList[posMoveListIndex] = rightCaptureMoveWhite;
                posMoveListIndex = posMoveListIndex + 1;
            }
            posMoveList[posMoveListIndex] = Tile_Count;
        }
    }
    else if (TileArr[index].piece.player = Player_Black)
    {
        TileEnum oneForwardMoveBlack = static_cast<TileEnum>(index - 8);
        TileEnum twoForwardMoveBlack = static_cast<TileEnum>(index - 16);
        TileEnum leftCaptureMoveBlack = static_cast<TileEnum>(index - 7);
        TileEnum rightCaptureMoveBlack = static_cast<TileEnum>(index - 9);

        // Calculation of non-capture moves
        // Pawn has not move yet, it can move two tiles forward
        if ((index >= Tile_A7) &&
            (index <= Tile_H7))
        {
            // One tile forward is occupied, nowhere to move
            if (TileArr[oneForwardMoveBlack].tileStatus == TileStatus_NotEmpty)
            {
                posMoveList[0] = Tile_Count;
            }
            // One tile forward is free, two file forward is occupied
            // Add index of one tile forward to list
            else if ((TileArr[oneForwardMoveBlack].tileStatus == TileStatus_Empty) &&
                     (TileArr[twoForwardMoveBlack].tileStatus == TileStatus_NotEmpty))
            {
                posMoveList[0] = oneForwardMoveBlack;
                posMoveList[1] = Tile_Count;
                posMoveListIndex = 1;
            }
            // One and two tiles forward are free
            // Add indexes of both tiles to list
            else if ((TileArr[oneForwardMoveBlack].tileStatus == TileStatus_Empty) &&
                     (TileArr[twoForwardMoveBlack].tileStatus == TileStatus_Empty))
            {
                posMoveList[0] = oneForwardMoveBlack;
                posMoveList[1] = twoForwardMoveBlack;
                posMoveList[2] = Tile_Count;
                posMoveListIndex = 2;
            }
        }
        // Pawn moved at least one, it can only move one tile forward
        else if ((index >= Tile_A6) &&
                 (index <= Tile_H6))
        {
            // One tile forward is occupied, nowhere to move
            if (TileArr[oneForwardMoveBlack].tileStatus == TileStatus_NotEmpty)
            {
                posMoveList[0] = Tile_Count;
            }
            // One tile forward is free, add index of one tile forward to list
            else if (TileArr[oneForwardMoveBlack].tileStatus == TileStatus_Empty)
            {
                posMoveList[0] = oneForwardMoveBlack;
                posMoveList[1] = Tile_Count;
                posMoveListIndex = 1;
            }
        }


        // Calculation of capture moves
        // Pawn is in left corner, can only capture through right
        if ((index == Tile_A2) ||
            (index == Tile_A3) ||
            (index == Tile_A4) ||
            (index == Tile_A5) ||
            (index == Tile_A6) ||
            (index == Tile_A7))
        {
            if ((TileArr[rightCaptureMoveBlack].tileStatus == TileStatus_NotEmpty) &&
                (TileArr[rightCaptureMoveBlack].piece.player == Player_White))
            {
                posMoveList[posMoveListIndex] = rightCaptureMoveBlack;
                posMoveList[posMoveListIndex + 1] = Tile_Count;
            }
        }
        // Pawn is in right corner, can only capture through left
        else if ((index == Tile_H2) ||
                 (index == Tile_H3) ||
                 (index == Tile_H4) ||
                 (index == Tile_H5) ||
                 (index == Tile_H6) ||
                 (index == Tile_H7))
        {
            if ((TileArr[leftCaptureMoveBlack].tileStatus == TileStatus_NotEmpty) &&
                (TileArr[leftCaptureMoveBlack].piece.player == Player_White))
            {
                posMoveList[posMoveListIndex] = leftCaptureMoveBlack;
                posMoveList[posMoveListIndex + 1] = Tile_Count;
            }
        }
        // Pawn is in middle, can capture both through left and right
        else if (((index > Tile_A2) && (index < Tile_H2)) ||
                 ((index > Tile_A3) && (index < Tile_H3)) ||
                 ((index > Tile_A4) && (index < Tile_H4)) ||
                 ((index > Tile_A5) && (index < Tile_H5)) ||
                 ((index > Tile_A6) && (index < Tile_H6)) ||
                 ((index > Tile_A7) && (index < Tile_H7)))
        {
            if ((TileArr[leftCaptureMoveBlack].tileStatus == TileStatus_NotEmpty) &&
                (TileArr[leftCaptureMoveBlack].piece.player == Player_White))
            {
                posMoveList[posMoveListIndex] = leftCaptureMoveBlack;
                posMoveListIndex = posMoveListIndex + 1;
            }
            if ((TileArr[rightCaptureMoveBlack].tileStatus == TileStatus_NotEmpty) &&
                (TileArr[rightCaptureMoveBlack].piece.player == Player_White))
            {
                posMoveList[posMoveListIndex] = rightCaptureMoveBlack;
                posMoveListIndex = posMoveListIndex + 1;
            }
            posMoveList[posMoveListIndex] = Tile_Count;
        }
    }
}

void ChessLogicCls::CalculatePossibleRookMoves(TileEnum index, TileEnum* posMoveList)
{


    if (TileArr[index].piece.player == Player_White)
    {

    }
}