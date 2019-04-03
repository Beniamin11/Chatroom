import QtQuick 2.0
import QtQuick.Controls 1.2

Item
{
    id: nickname
    anchors.centerIn: parent
    width: 350
    height: 150

    signal setButtonPressed
    signal cancelButtonPressed
    property string nameInput: inputNickname.text
    property string setOrTryAgain: "Set Nickname"

    function focusInputName()
    {
        inputNickname.forceActiveFocus()
    }

    Rectangle
    {
        anchors.fill: parent
        color: "#D8D8D8"
    }

    Text{
        anchors { bottom: ntextinput.top; bottomMargin: 20 }
        height: 30
        width: parent.width
        text: cmw.popupTitle
        horizontalAlignment: Qt.AlignCenter
        font.pixelSize: 20
    }

    Rectangle
    {
        id: ntextinput
        anchors { left: parent.left; right: parent.right; verticalCenter: parent.verticalCenter
                  rightMargin: 10; leftMargin: 10 }
        color: "#FFFFFF"
        height: 30
        border{ width: 1; color: "lightblue" }

        TextInput
        {
            id: inputNickname
            clip: true
            anchors { fill: parent; rightMargin: 5; leftMargin: 5 }
            font { pixelSize: 16; family: "TimesNewRoman"; }
            maximumLength: 25
            onAccepted: if( text != "" && text != " ") { nickname.setButtonPressed(); text = ""; }
            Keys.onPressed: if(!text.trim())    text = "";
        }
    }

    Button
    {
        id: setNickname
        anchors { left: parent.left; right: parent.horizontalCenter; top: ntextinput.bottom; margins: 20 }
        height: 30
        text: "Set"
        enabled: ( inputNickname.text == "" || inputNickname.text == " ") ? false : true
        isDefault: true
        onClicked: parent.setButtonPressed()
    }

    Button
    {
        id: cancelSet
        anchors { left: parent.horizontalCenter; right: parent.right; top: ntextinput.bottom; margins: 20 }
        height: 30
        text: "Cancel"
        onClicked: parent.cancelButtonPressed()
    }

}
