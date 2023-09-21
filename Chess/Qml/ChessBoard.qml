import QtQuick 2.9

Rectangle {
    id: root
    //color: "#ffcccccc";

    readonly property int squareSize: Math.min(8 * width / 10, 8 * height/ 10) / 8;

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
            x: file * squareSize + squareSize;
            y: (7 - rank) * squareSize + squareSize;

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

    // Board Border
    // Top
    Repeater {
        model: 8

        Rectangle {
            width: squareSize
            height: squareSize

            color: "#d18b47";

            Text {
                id: textArea
                anchors.centerIn: parent
                text: {
                    if (index === 0)
                    {
                        return "A";
                    }
                    else if (index === 1)
                    {
                        return "B";
                    }
                    else if (index === 2)
                    {
                        return "C";
                    }
                    else if (index === 3)
                    {
                        return "D";
                    }
                    else if (index === 4)
                    {
                        return "E";
                    }
                    else if (index === 5)
                    {
                        return "F";
                    }
                    else if (index === 6)
                    {
                        return "G";
                    }
                    else if (index === 7)
                    {
                        return "H";
                    }
                }
            }

            x: (index + 1) * squareSize
            y: 0
        }
    }

    // Bottom
    Repeater {
        model: 8

        Rectangle {
            width: squareSize
            height: squareSize

            color: "#d18b47";

            Text {
                id: textArea
                anchors.centerIn: parent
                text: {
                    if (index === 0)
                    {
                        return "A";
                    }
                    else if (index === 1)
                    {
                        return "B";
                    }
                    else if (index === 2)
                    {
                        return "C";
                    }
                    else if (index === 3)
                    {
                        return "D";
                    }
                    else if (index === 4)
                    {
                        return "E";
                    }
                    else if (index === 5)
                    {
                        return "F";
                    }
                    else if (index === 6)
                    {
                        return "G";
                    }
                    else if (index === 7)
                    {
                        return "H";
                    }
                }
            }

            x: (index + 1) * squareSize
            y: 9 * squareSize
        }
    }

    // Left
    Repeater {
        model: 8

        Rectangle {
            width: squareSize
            height: squareSize

            color: "#d18b47";

            Text {
                id: textArea
                anchors.centerIn: parent
                text: "" + (8 - index)
            }

            x: 0
            y: (index + 1) * squareSize
        }
    }

    // Right
    Repeater {
        model: 8

        Rectangle {
            width: squareSize
            height: squareSize

            color: "#d18b47";

            Text {
                id: textArea
                anchors.centerIn: parent
                text: "" + (8 - index)
            }

            x: 9 * squareSize
            y: (index + 1) * squareSize
        }
    }

    function calculateIndex(file, rank)
    {
        return 8 * (7 - rank) + file;
    }
} // Rectangle