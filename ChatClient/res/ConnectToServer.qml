import QtQuick 2.0
import QtQuick.Controls 1.2

Item
{
    id: connect
    anchors.centerIn: parent
    width: 450
    height: 300

    signal tryConnectPressed
    signal cancelPressed
    signal showHistoryPressed

    property string ipAddress
    property string m_port
    property string titleText: "Connect to server:"

    function clientConnect(_ip, _port)
    {
        ipAddress = _ip
        m_port = _port
        titleText = "Connecting..."
        tryConnectPressed();
    }

    Connections {
        target: cmw
        onConnectedChanged: if(!cmw.connected)  titleText = "Error! Try Again!"
    }

    Rectangle{ anchors.fill: parent; color: "#D8D8D8" }

    Text{
        id: textConnect
        anchors { top: connect.top;  topMargin: 20 }
        height: 40;  width: parent.width - 20
        text: titleText
        horizontalAlignment: Qt.AlignCenter
        wrapMode: Text.WordWrap
        font.pixelSize: 20
    }

    Text{
        id: ipText
        anchors { left: parent.left; right: parent.horizontalCenter; top:textConnect.bottom
                  leftMargin: 10; rightMargin: 15 }
        height: contentHeight
        text: "IP Address: ";   font.pixelSize: 16
    }

    Rectangle
    {
        id: ip
        anchors { left: parent.left; right: parent.horizontalCenter; top:ipText.bottom
                  leftMargin: 10; topMargin: 10; rightMargin: 15 }
        color: "#FFFFFF";  height: 30
        border{ width: 1; color: "lightblue" }
        TextInput
        {
            id: inputIP
            clip: true
            anchors { fill: parent; rightMargin: 5; leftMargin: 5 }
            text: "127.0.0.1"
            maximumLength: 16
            font { pixelSize: 16; family: "TimesNewRoman"; }
            Keys.onTabPressed: inputPort.forceActiveFocus()
            onAccepted: if( text !== "") { clientConnect(inputIP.text, inputPort.text)  }
        }
    }

    Text{
        id: portText
        anchors { right: parent.right; left: parent.horizontalCenter; top:textConnect.bottom
                  rightMargin: 10; leftMargin: 15 }
        height: contentHeight
        text: "Port: ";   font.pixelSize: 16        
    }
    Rectangle
    {
        id: port
        anchors { right: parent.right; left: parent.horizontalCenter; top:portText.bottom
                  rightMargin: 10; topMargin: 10; leftMargin: 15}
        color: "#FFFFFF";  height: 30
        border{ width: 1; color: "lightblue" }
        TextInput
        {
            id: inputPort
            clip: true
            text: "1234"
            maximumLength: 6
            validator: IntValidator{bottom: 1; top:9999}
            anchors { fill: parent; rightMargin: 5; leftMargin: 5 }
            font { pixelSize: 16; family: "TimesNewRoman"; }
            Keys.onBacktabPressed: inputIP.forceActiveFocus()
            Keys.onReturnPressed: if( text !== "") { clientConnect(inputIP.text, inputPort.text)  }
            Keys.onEnterPressed: if( text !== "") { clientConnect(inputIP.text, inputPort.text) }
        }
    }

    Button
    {
        id: tryConnect
        anchors { left: parent.left; right: parent.horizontalCenter; top: ip.bottom; margins: 20 }
        height: 30
        text: "Connect"
        isDefault: true
        onClicked: clientConnect(inputIP.text, inputPort.text)
        Keys.onBacktabPressed: inputPort.forceActiveFocus()
    }

    Button
    {
        id: cancel
        anchors { left: parent.horizontalCenter; right: parent.right; top: port.bottom; margins: 20 }
        height: 30
        text: "Cancel"
        onClicked: cancelPressed()
    }

    Button
    {
        id: history
        anchors { left: tryConnect.horizontalCenter; right: cancel.horizontalCenter; top: cancel.bottom; topMargin: 40 }
        height: 30
        text: "Show History"
        onClicked: showHistoryPressed()
    }


    Component.onCompleted: inputIP.forceActiveFocus();
}
