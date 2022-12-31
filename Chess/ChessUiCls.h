#ifndef CHESSUICLS_H
#define CHESSUICLS_H

#include <QObject>

#include "ChessLogicCls.h"

class ChessUiCls : public QObject
{
	Q_OBJECT

public:
	ChessLogicCls chessLogicObj;

	explicit ChessUiCls(QObject* parent = nullptr);
};

#endif // !CHESSUICLS_H
