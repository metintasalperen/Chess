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
	PlayerEnum GetTurn() override;

	UiChessIfc* GetItsUiChessIfc();

private:
	void SwitchTurn();

	bool CheckMoveValidity(const MoveStc& from, const MoveStc& to);

	// TODO: Add en passant
	bool CheckPawnMoveValidity(const MoveStc& from, const MoveStc& to);
	bool CheckRookMoveValidity(const MoveStc& from, const MoveStc& to);
	bool CheckKnightMoveValidity(const MoveStc& from, const MoveStc& to);
	bool CheckBishopMoveValidity(const MoveStc& from, const MoveStc& to);
	bool CheckQueenMoveValidity(const MoveStc& from, const MoveStc& to);

	// TODO: Add castling
	// TODO: Check whether move cause king to be under attack
	bool CheckKingMoveValidity(const MoveStc& from, const MoveStc& to);
};

#endif