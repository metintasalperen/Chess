import QtQuick 2.9

Rectangle {
    color: "#ffcccccc";

    readonly property int squareSize: Math.min(width, height) / 8;

    // Board
    Repeater {
        model: 64;

        Rectangle {
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
        } // Rectangle
    } // Repeater
} // Rectangle