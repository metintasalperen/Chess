#ifndef CHESSCLS_H
#define CHESSCLS_H

#include <cstdint>
#include <vector>

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
	bool CastlingAvailable[Player_Count];
	bool IsLastMoveCastling;
	GameStateEnum GameState;

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
	GameStateEnum GetGameState() override;

	UiChessIfc* GetItsUiChessIfc();

private:
	void SwitchTurn();

	void MovePiece(const MoveStc& from, const MoveStc& to);

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

	std::vector<MoveStc> CalculatePossibleMoves(const MoveStc& index);

	MoveStc FindKing(const PlayerEnum& color);

	// This method only called if CheckMoveValidity methods returns true
	// So no need to check trivial move controls again
	bool CheckMoveExposesKing(const MoveStc& from, const MoveStc& to);

	bool IsCheckmate(const MoveStc& from, const MoveStc& to);
};

#endif