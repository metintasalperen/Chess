import QtQuick 2.9

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
                    console.log(row, col)
                }
            }
        }
    }

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
                    if ( (index >= 8) &&
                         (index < 24) )
                    {
                        return "♟"
                    }
                    else if ( (index === 0) ||
                              (index === 7) ||
                              (index === 24) ||
                              (index === 31) )
                    {
                        return "♜"
                    }
                    else if ( (index === 1) ||
                              (index === 6) ||
                              (index === 25) ||
                              (index === 30) )
                    {
                        return "♞"
                    }
                    else if ( (index === 2) ||
                              (index === 5) ||
                              (index === 26) ||
                              (index === 29) )
                    {
                        return "♝"
                    }
                    else if ( (index === 3) ||
                              (index === 27) )
                    {
                        return "♛"
                    }
                    else if ( (index === 4) ||
                              (index === 28) )
                    {
                        return "♚"
                    }
                    else
                    {
                        return ""
                    }
                }
            }
        }
    }
}
