#ifndef UICLS_H
#define UICLS_H

#include <QObject>
#include <cstdlib>

#include "StructPkg.h"
#include "UiChessIfc.h"

class UiCls : public QObject
{
	Q_OBJECT
public:
	explicit UiCls(QObject* parent = nullptr);

public slots:
	// true: Square is occupied
	// false: Square is empty
	bool isSquareOccupied(unsigned int file, unsigned int rank);

	// -1: No piece
	//  0: Pawn
	//  1: Rook
	//  2: Knight
	//  3: Bishop
	//  4: Queen
	//  5: King
	int getPieceType(unsigned int file, unsigned int rank);

	// -1: No piece
	//  0: White
	//  1: Black
	int getPieceColor(unsigned int file, unsigned int rank);

	bool getUserInput(unsigned int fromFile, 
		unsigned int fromRank,
		unsigned int toFile,
		unsigned int toRank);

private:
	TableStc* TablePtr;
	UiChessIfc* ItsUiChessIfc;

public:
	void SetItsUiChessIfc(UiChessIfc* ifc);
	void UpdateTableState();

private:
	uint32_t CalculateIndex(uint32_t file, uint32_t rank);
};

#endif