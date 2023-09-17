import QtQuick 2.9
import QtQuick.Window 2.2
//import "./ChessBoard.qml"

Window {
    visible: true
    width: 480
    height: 480
    title: "Chess"
    
    ChessBoard {
        width: 480
        height: 480
    }
}
