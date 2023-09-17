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

                source: {
                    var color = UiObject.getPieceColor(square.file, square.rank);
                    var type = UiObject.getPieceType(square.file, square.rank);

                    return setPicture(color, type);
                }

                MouseArea {
                    width: square.width;
                    height: square.height;

                    onClicked: {
                        if (!root.fromClicked)
                        {
                            var occupied = UiObject.isSquareOccupied(square.file, square.rank);
                        
                            if (occupied)
                            {
                                root.fromClicked = true;
                                root.fromFile = file;
                                root.fromRank = rank;
                            }
                            // Else: Do nothing, player clicked empty square
                        }
                        else
                        {
                            root.fromClicked = false;
                            var moveValidity = UiObject.getUserInput(root.fromFile, root.fromRank, square.file, square.rank);
                        
                            if (moveValidity)
                            {
                                var index = calculateIndex(root.fromFile, root.fromRank);
                                var image = pieceImages[indexes[index]];

                                pieceImage.source = image.source;
                                image.source = "empty.png";
                            }
                        }
                    }
                }
            }
        } // Rectangle
    } // Repeater



    // Function definitions
    function setPicture(color, type)
    {
        if (color == 0)
        {
            if (type == 0)
            {
                return "white_pawn.svg";
            }
            else if (type == 1)
            {
                return "white_rook.svg";
            }
            else if (type == 2)
            {
                return "white_knight.svg";
            }
            else if (type == 3)
            {
                return "white_bishop.svg";
            }
            else if (type == 4)
            {
                return "white_queen.svg";
            }
            else if (type == 5)
            {
                return "white_king.svg";
            }
        }
        else if (color == 1)
        {
            if (type == 0)
            {
                return "black_pawn.svg";
            }
            else if (type == 1)
            {
                return "black_rook.svg";
            }
            else if (type == 2)
            {
                return "black_knight.svg";
            }
            else if (type == 3)
            {
                return "black_bishop.svg";
            }
            else if (type == 4)
            {
                return "black_queen.svg";
            }
            else if (type == 5)
            {
                return "black_king.svg";
            }
        }
        else
        {
            return "empty.png";
        }
    }
    
    function calculateIndex(file, rank)
    {
        return 8 * (7 - rank) + file;
    }
} // Rectangle