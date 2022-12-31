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

	QVariant handlePieceClicked(int index);

private:
	void ResetPosMoveList();
};

#endif // !CHESSUICLS_H
