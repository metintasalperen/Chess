#ifndef UICLS_H
#define UICLS_H

#include <QObject>
#include <cstdlib>

#include "StructPkg.h"
#include "UiChessIfc.h"
#include "Headers/ConstPkg.h"

class UiCls : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList imageData READ getImageData NOTIFY imageDataChanged)

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

	// 0: White
	// 1: Black
	int getTurn();

	void updateTable();

signals:
	void imageDataChanged();

public:
	QStringList getImageData() const;

private:
	TableStc* TablePtr;
	UiChessIfc* ItsUiChessIfc;

public:
	QStringList imageList;

	void SetItsUiChessIfc(UiChessIfc* ifc);

private:
	void UpdateTableState();
	uint32_t CalculateIndex(uint32_t file, uint32_t rank);
};

#endif