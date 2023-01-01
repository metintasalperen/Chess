#include "ChessUiCls.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif

ChessUiCls::ChessUiCls(QObject* parent)
    : QObject(parent)
{
    ResetPosMoveList();
}

void ChessUiCls::ResetPosMoveList()
{
    for (int i = 0; i < Tile_Count; i++)
    {
        posMoveList[i] = Tile_Count;
    }
}

QVariant ChessUiCls::getPieceId(int index)
{
    if ((index >= Tile_A1) &&
        (index <= Tile_H8))
    {
        return chessLogicObj.GetPieceId(static_cast<TileEnum>(index));
    }
    else
    {
        return Tile_Count;
    }
}

QVariant ChessUiCls::getPlayerTurn()
{
    return chessLogicObj.GetPlayerTurn();
}

QVariant ChessUiCls::getPieceClicked()
{
    return chessLogicObj.GetPieceClicked();
}

QVariant ChessUiCls::handlePieceClicked(int index)
{
    QVariantList moveList;

    if ((index >= Tile_A1) &&
        (index <= Tile_H8))
    {
        ResetPosMoveList();
        
        chessLogicObj.CalculatePossibleMoves(static_cast<TileEnum>(index), &posMoveList[0]);

        for (int i = 0; (i < Tile_Count) && (posMoveList[i] != Tile_Count); i++)
        {
#ifdef DEBUG
            qDebug() << posMoveList[i];
#endif
            moveList << posMoveList[i];
        }
    }
    else
    {
        moveList << Tile_Count;
    }

    return moveList;
}

QVariant ChessUiCls::handlePieceClicked2(int index)
{
    return QVariant();
}