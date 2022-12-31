import QtQuick 2.9
import ChessEnums 1.0

// 8x8 Chess Board
Rectangle {
    id: chessBoardContainer
    width: parent.width * 4 / 5
    height: parent.height * 4 / 5
    x: width / 10
    y: height / 10

    Repeater {
        id: tileRepeater
        model: 64

        Rectangle {
            property int row: Math.floor(index / 8)
            property int col: index % 8

            x: col * chessBoardContainer.width / 8
            y: (7 - row) * chessBoardContainer.height / 8

            width: chessBoardContainer.width / 8
            height: chessBoardContainer.height / 8

            color: {
                var even = ((row + col) % 2) == 0
                return even ? "#ffaa88" : "#ff8b47"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var index = calculateIndex(row, col)
                    var pieceId = chessUiObj.getPieceId(index)

                    if (pieceId != ChessEnums.Piece_Count)
                    {
                        var posMoveList = chessUiObj.handlePieceClicked(index)

                        for (var i = 0; i < posMoveList.length; i++)
                        {
                            console.log("item", i, ": ", posMoveList[i])
                        }
                    }
                } // onClicked
            } // MouseArea
        } // Rectangle
    } // Repeater

    Repeater {
        id: pieceRepeater
        model: 32

        Item {
            z: 1
            x: (index % 8) * chessBoardContainer.width / 8
            y: {
                if (index < 8)
                {
                    return chessBoardContainer.width * 7 / 8
                }
                else if (index < 16)
                {
                    return chessBoardContainer.width * 6 / 8
                }
                else if (index < 24)
                {
                    return chessBoardContainer.width / 8
                }
                else
                {
                    return 0
                }
            }

            width: chessBoardContainer.width / 8
            height: chessBoardContainer.height / 8

            visible: true

            Text {
                color: index < 16 ? "#eee" : "#444"
                
                width: parent.width
                height: parent.height
                
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

                font.pixelSize: width / 2

                text: {
                    if ( (index >= ChessEnums.Piece_WhitePawn1) &&
                         (index <= ChessEnums.Piece_BlackPawn8) )
                    {
                        return "♟"
                    }
                    else if ( (index === ChessEnums.Piece_WhiteRook1) ||
                              (index === ChessEnums.Piece_WhiteRook2) ||
                              (index === ChessEnums.Piece_BlackRook1) ||
                              (index === ChessEnums.Piece_BlackRook2) )
                    {
                        return "♜"
                    }
                    else if ( (index === ChessEnums.Piece_WhiteKnight1) ||
                              (index === ChessEnums.Piece_WhiteKnight2) ||
                              (index === ChessEnums.Piece_BlackKnight1) ||
                              (index === ChessEnums.Piece_BlackKnight2) )
                    {
                        return "♞"
                    }
                    else if ( (index === ChessEnums.Piece_WhiteBishop1) ||
                              (index === ChessEnums.Piece_WhiteBishop2) ||
                              (index === ChessEnums.Piece_BlackBishop1) ||
                              (index === ChessEnums.Piece_BlackBishop2) )
                    {
                        return "♝"
                    }
                    else if ( (index === ChessEnums.Piece_WhiteQueen) ||
                              (index === ChessEnums.Piece_BlackQueen) )
                    {
                        return "♛"
                    }
                    else if ( (index === ChessEnums.Piece_WhiteKing) ||
                              (index === ChessEnums.Piece_BlackKing) )
                    {
                        return "♚"
                    }
                    else
                    {
                        return ""
                    }
                } // text
            } // Text
        } // Item
    } // Repeater

    function calculateIndex(row, col)
    {
        return (8 * row) + col
    }
} // Rectangle
