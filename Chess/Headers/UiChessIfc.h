#ifndef UICHESSIFC_H
#define UICHESSIFC_H

#include "EnumPkg.h"
#include "StructPkg.h"

// Required: UiCls.h
// Provided: ChessCls.h
class UiChessIfc
{
public:
	virtual bool ProcessUserInput(const MoveStc& from, const MoveStc& to) = 0;
	virtual void UpdateTableState(TableStc*& table) = 0;
	virtual PlayerEnum GetTurn() = 0;
	virtual GameStateEnum GetGameState() = 0;
};

#endif