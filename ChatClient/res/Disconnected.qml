import QtQuick 2.0
import QtQuick.Controls 1.2

Item
{
    id: disconnected
    anchors.centerIn: parent
    width: 350
    height: 150

    signal tryReconnectPressed
    signal cancelReconnectPressed

    Rectangle{ anchors.fill: parent; color: "#D8D8D8" }

    Text{
        anchors{ top: disconnected.top; topMargin: 20 }
        height: 60
        width: parent.width - 20
        text: "There was a problem connecting to the server"
        horizontalAlignment: Qt.AlignCenter
        wrapMode: Text.WordWrap
        font.pixelSize: 20
    }

    Button
    {
        id: tryAgain
        anchors{ left: parent.left; right: parent.horizontalCenter; bottom: disconnected.bottom; margins: 20 }
        isDefault: true
        height: 30
        text: "Try Again"
        onClicked: tryReconnectPressed()
    }
    Button
    {
        id: cancel
        anchors { left: parent.horizontalCenter; right: parent.right; bottom: disconnected.bottom; margins: 20 }
        height: 30
        text: "Cancel"
        onClicked: cancelReconnectPressed()
    }

}
