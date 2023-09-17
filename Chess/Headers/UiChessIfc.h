#ifndef UICHESSIFC_H
#define UICHESSIFC_H

#include "StructPkg.h"

// Required: UiCls.h
// Provided: ChessCls.h
class UiChessIfc
{
public:
	virtual bool ProcessUserInput(const MoveStc& from, const MoveStc& to) = 0;
	virtual void UpdateTableState(TableStc*& table) = 0;
};

#endif