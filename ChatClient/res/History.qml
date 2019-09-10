import QtQuick 2.0
import QtQuick.Controls 1.2

Item {
    id: root
    anchors.fill: parent

    signal backPressed

    Rectangle
    {
        id: conversation
        anchors { fill: parent; leftMargin: 30; rightMargin: 30; topMargin: 70; bottomMargin: 30; }
        color: "#FFFFFF"
        border { width: 1; color: "lightblue" }

        property real windowDimension: parent.height + parent.width
        property int fontSize: if(windowDimension < 850)        return 12
                               else if(windowDimension > 2000 ) return 20
                                    else                        return 16
        Text {
            anchors {fill:  parent; margins: 40 }
            id: convHist
            font.pixelSize: conversation.fontSize
            text: cmw.convHistory
        }

    }

    Button {
        id: back
        anchors { top: parent.top; left: parent.left; leftMargin: 40; topMargin: 20; bottom: conversation.top; bottomMargin: 20; }
        width: 60;
        Text {
            anchors.centerIn: parent
            font.pixelSize: conversation.fontSize
            text: "Back"
        }
        onPressedChanged: backPressed()
    }
}
