#ifndef CHESSUICLS_H
#define CHESSUICLS_H

#include <QObject>
#include <QVariant>

#include "ChessLogicCls.h"

class ChessUiCls : public QObject
{
	Q_OBJECT

public:
	ChessLogicCls chessLogicObj;
	TileEnum posMoveList[Tile_Count];


	explicit ChessUiCls(QObject* parent = nullptr);

public slots:
	// returns the id of piece in given tile index
	QVariant getPieceId(int index);
	// returns player turn
	QVariant getPlayerTurn();
	// returns whether a piece is clicked to move or not
	QVariant getPieceClicked();

	// handles when a piece is clicked first time, returns possible moves
	QVariant handlePieceClicked(int index);
	// handles when a tile is clicked so that piece can move there
	QVariant handlePieceClicked2(int index);

private:
	void ResetPosMoveList();
};

#endif // !CHESSUICLS_H
