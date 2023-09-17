#include "Headers/UiCls.h"

UiCls::UiCls(QObject* parent)
    : QObject(parent),
      ItsUiChessIfc(nullptr),
      TablePtr(nullptr)
{

}

bool UiCls::isSquareOccupied(unsigned int file, unsigned int rank)
{
    uint32_t index = CalculateIndex(file, rank);

    if (TablePtr->Square[index].State == SquareState_Empty)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int UiCls::getPieceType(unsigned int file, unsigned int rank)
{
    uint32_t index = CalculateIndex(file, rank);

    if (TablePtr->Square[index].State == SquareState_Empty)
    {
        return -1;
    }
    else
    {
        return static_cast<int>(TablePtr->Square[index].Piece.Name);
    }
}

int UiCls::getPieceColor(unsigned int file, unsigned int rank)
{
    uint32_t index = CalculateIndex(file, rank);

    if (TablePtr->Square[index].State == SquareState_Empty)
    {
        return -1;
    }
    else
    {
        return static_cast<int>(TablePtr->Square[index].Piece.Owner);
    }
}

bool UiCls::getUserInput(unsigned int fromFile, unsigned int fromRank, unsigned int toFile, unsigned int toRank)
{
    MoveStc from = { static_cast<FileEnum>(fromFile), static_cast<RankEnum>(fromRank) };
    MoveStc to = { static_cast<FileEnum>(toFile), static_cast<RankEnum>(toRank) };

    bool result = ItsUiChessIfc->ProcessUserInput(from, to);

    if (result == true)
    {
        ItsUiChessIfc->UpdateTableState(TablePtr);
    }

    return result;
}

int UiCls::getTurn()
{
    return static_cast<int>(ItsUiChessIfc->GetTurn());
}

void UiCls::SetItsUiChessIfc(UiChessIfc* ifc)
{
    ItsUiChessIfc = ifc;
}

void UiCls::UpdateTableState()
{
    ItsUiChessIfc->UpdateTableState(TablePtr);
}

uint32_t UiCls::CalculateIndex(uint32_t file, uint32_t rank)
{
    uint32_t index = 8 * (7 - rank) + file;
    return index;
}
