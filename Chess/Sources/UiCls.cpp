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

int UiCls::getGameState()
{
    return static_cast<int>(ItsUiChessIfc->GetGameState());
}

void UiCls::restartGame()
{
    ItsUiChessIfc->Initialize();
}

void UiCls::updateTable()
{
    UpdateTableState();

    imageList.clear();

    for (unsigned int i = 0; i < 64; i++)
    {
        if (TablePtr->Square[i].State == SquareState_Empty)
        {
            imageList << QString::fromStdString(EMPTY_IMAGE);
        }
        else
        {
            switch (TablePtr->Square[i].Piece.Name)
            {
                case Piece_Pawn:
                {
                    if (TablePtr->Square[i].Piece.Owner == Player_White)
                    {
                        imageList << QString::fromStdString(WHITE_PAWN);
                    }
                    else
                    {
                        imageList << QString::fromStdString(BLACK_PAWN);
                    }

                    break;
                }
                case Piece_Rook:
                {
                    if (TablePtr->Square[i].Piece.Owner == Player_White)
                    {
                        imageList << QString::fromStdString(WHITE_ROOK);
                    }
                    else
                    {
                        imageList << QString::fromStdString(BLACK_ROOK);
                    }

                    break;
                }
                case Piece_Knight:
                {
                    if (TablePtr->Square[i].Piece.Owner == Player_White)
                    {
                        imageList << QString::fromStdString(WHITE_KNIGHT);
                    }
                    else
                    {
                        imageList << QString::fromStdString(BLACK_KNIGHT);
                    }

                    break;
                }
                case Piece_Bishop:
                {
                    if (TablePtr->Square[i].Piece.Owner == Player_White)
                    {
                        imageList << QString::fromStdString(WHITE_BISHOP);
                    }
                    else
                    {
                        imageList << QString::fromStdString(BLACK_BISHOP);
                    }

                    break;
                }
                case Piece_Queen:
                {
                    if (TablePtr->Square[i].Piece.Owner == Player_White)
                    {
                        imageList << QString::fromStdString(WHITE_QUEEN);
                    }
                    else
                    {
                        imageList << QString::fromStdString(BLACK_QUEEN);
                    }

                    break;
                }
                case Piece_King:
                {
                    if (TablePtr->Square[i].Piece.Owner == Player_White)
                    {
                        imageList << QString::fromStdString(WHITE_KING);
                    }
                    else
                    {
                        imageList << QString::fromStdString(BLACK_KING);
                    }

                    break;
                }
                default:
                {
                    imageList << QString::fromStdString(EMPTY_IMAGE);

                    break;
                }
            }
        }
    }

    emit imageDataChanged();
}

QStringList UiCls::getImageData() const
{
    return imageList;
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
