import QtQuick 2.9

Rectangle {
    id: root
    color: "#ffcccccc";

    readonly property int squareSize: Math.min(width, height) / 8;

    property bool fromClicked: false;
    property int fromFile: 0;
    property int fromRank: 0;

    property var pieceImages: []
    property var indexes: []

    // Board
    Repeater {
        id: board
        model: 64;

        Rectangle {
            id: square
            property int rank: Math.floor(index / 8);
            property int file: index % 8;

            z: 0;
            x: file * squareSize;
            y: (7 - rank) * squareSize;

            height: squareSize;
            width: squareSize;

            property bool showBorder: false;
            border.color: "#009900";
            border.width: {
                if (showBorder)
                {
                    return 2;
                }
                else
                {
                    return 0;
                }
            }

            color: {
                var even = ((rank + file) % 2) == 0;

                if (even)
                {
                    return "#d18b47";
                }
                else
                {
                    return "#ffce93";
                }
            } // color

            Image {
                id: pieceImage;

                Component.onCompleted: {
                    pieceImages.push(pieceImage);
                    indexes.push(calculateIndex(square.file, square.rank));
                }

                width: 45;
                height: 45;

                x: (parent.width - width) / 2;
                y: (parent.height - height) / 2;

                source: UiObject.imageData[calculateIndex(square.file, square.rank)]

                MouseArea {
                    width: square.width;
                    height: square.height;

                    onClicked: {
                        // Piece selection
                        if (!root.fromClicked)
                        {
                            var turn = UiObject.getTurn();
                            var color = UiObject.getPieceColor(square.file, square.rank);

                            // if player selects its own piece, set green border around the piece
                            if (turn == color)
                            {
                                square.showBorder = !square.showBorder;

                                root.fromFile = square.file;
                                root.fromRank = square.rank;

                                root.fromClicked = true;
                            }
                        }
                        // Destination selection
                        else
                        {
                            root.fromClicked = false;

                            var moveValidity = UiObject.getUserInput(root.fromFile, root.fromRank, square.file, square.rank);
                            if (moveValidity)
                            {
                                UiObject.updateTable();
                            }

                            var fromSquare = board.itemAt(indexes[calculateIndex(root.fromFile, root.fromRank)]);
                            fromSquare.showBorder = !fromSquare.showBorder;
                        }
                    }
                }
            }
        } // Rectangle
    } // Repeater

    function calculateIndex(file, rank)
    {
        return 8 * (7 - rank) + file;
    }
} // Rectangle