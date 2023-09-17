#ifndef CHESSCLS_H
#define CHESSCLS_H

#include <cstdint>

#include "EnumPkg.h"
#include "StructPkg.h"
#include "UiChessIfc.h"

// Responsible for;
// * Holding table state
// * Processing user moves
// * Calculating checkmate/stalemate
class ChessCls : public UiChessIfc
{
private:
	TableStc Table;
	PlayerEnum Turn;
	uint32_t TurnCount;

public:
	// Initializers
	ChessCls();
	void Initialize();

private:
	uint32_t CalculateIndex(uint32_t file, uint32_t rank);
	uint32_t CalculateIndex(const FileEnum& file, const RankEnum& rank);

public:
	bool ProcessUserInput(const MoveStc& from, const MoveStc& to) override;
	void UpdateTableState(TableStc*& table) override;

	UiChessIfc* GetItsUiChessIfc();
};

#endif