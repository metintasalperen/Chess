#ifndef CHESSCLS_H
#define CHESSCLS_H

#include <cstdint>

#include "EnumPkg.h"
#include "StructPkg.h"

// Responsible for;
// * Holding table state
// * Processing user moves
// * Calculating checkmate/stalemate
class ChessCls
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
};

#endif