import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import ChatWindow 1.0

ApplicationWindow {
    title: cmw.nickname + " - " + otherUser
    id: privateWindow
    width: 400
    height: 350    
    color: "#E6E6E6"
    minimumHeight: 250
    minimumWidth: 300

    property string otherUser
    property variant pmModel
    property bool otherActive: true

    onClosing:
    {
        cmw.sendCommand(ChatWindow.ClosePmWindow, otherUser)
        destroy()
    }

    function sendMessage(message)
    {
        cmw.sendCommand(ChatWindow.PM, otherUser + '\n' + message)
    }    

    Connections {
        target: cmw
        onFocusPmWindow: if(otherUser == other)    privateWindow.requestActivate();
        onOtherUserChanged: if(otherUser == other) otherUser = cmw.otherUser
    }

    Rectangle {
       id: receiverName
       anchors {top: parent.top; left: parent.left; right: parent.right; margins: 4}
       height: 22
       Text{ anchors.centerIn: parent; font.pixelSize: 18; color: "#000000"; text: otherUser }
       color: "#F3F781"
    }

    Rectangle
    {
        id: pm
        anchors { left: parent.left; right: parent.right; top: receiverName.bottom; bottom: messageLineEdit.top; margins: 8 }
        color: "#FFFFFF"
        border { width: 1; color: "lightblue" }

        ListView {
            property real pmMargin: width/4
            id: pmContent
            anchors { fill: parent; margins: 5 }
            model: pmModel
            clip: true
            spacing: 3
            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.StopAtBounds
            delegate: TextEdit{ id: pmText
                anchors {
                    left: cmw.getModel(otherUser).getAlign(index) ? undefined : parent.left;
                    right: cmw.getModel(otherUser).getAlign(index) ? parent.right : undefined;
                    margins: 6 }
                readOnly: true
                selectByMouse: true
                mouseSelectionMode: TextInput.SelectCharacters
                font { pixelSize: 15; family: "TimesNewRoman" }
                text: lineMessage
                textFormat: Text.RichText
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignLeft
                color: "black"                
                onContentWidthChanged: if(contentWidth > parent.width - pmContent.pmMargin) width = parent.width - pmContent.pmMargin                
                onLinkActivated: Qt.openUrlExternally(link)
                onLinkHovered: MouseArea.cursorShape = Qt.OpenHandCursor

                Rectangle {
                    anchors {
                        right: cmw.getModel(otherUser).getAlign(index) ? pmText.right : undefined;
                        left: cmw.getModel(otherUser).getAlign(index) ? undefined : pmText.left
                        rightMargin: cmw.getModel(otherUser).getAlign(index) ? -5 : 0;
                        leftMargin: cmw.getModel(otherUser).getAlign(index) ? 0 : -5;
                        top: pmText.top; bottom: pmText.bottom }
                    width: pmText.width + 8; radius: 4
                    color: cmw.getModel(otherUser).getColor(index); opacity: 0.5
                }
            }
            onContentHeightChanged: incrementCurrentIndex()
            }
    }

    TextArea
    {
        function send() {sendMessage(text); text = "" }

        id: messageLineEdit
        height: 50
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: sendButton.left
            bottomMargin: 10
            rightMargin: 10
            leftMargin: 10
        }
        clip: true
        wrapMode: Text.Wrap
        font { pixelSize: 16; family: "TimesNewRoman" }
        onTextChanged: if(length > 2001)   text = text.slice(0,2000)
        Keys.onPressed: if(!text.trim())    text = "";
        Keys.onTabPressed: if(sendButton.enabled)   sendButton.forceActiveFocus()
        Keys.onEnterPressed: if( sendButton.enabled )  send()
        Keys.onReturnPressed: if(  sendButton.enabled  && !(event.modifiers & Qt.ShiftModifier)) send()
                              else if( sendButton.enabled )
                                  { var temp = cursorPosition;
                                    text = text.slice(0,temp) + '\n' + text.slice(temp, text.length);
                                    cursorPosition = temp +1 }        
    }

    Button
    {
        id: sendButton
        width: parent.width / 8
        height: 25
        anchors { right: parent.right; rightMargin: 8; verticalCenter: messageLineEdit.verticalCenter }
        text: "Send"
        enabled: (messageLineEdit.text != "" && messageLineEdit.text != " ") ? true : false
        isDefault: true
        onClicked: { sendMessage(messageLineEdit.text); messageLineEdit.text = "" }
    }

    Component.onCompleted: {
        console.log("OtherUser: " + cmw.otherUser)
        otherUser = cmw.otherUser
        pmModel = cmw.getModel(otherUser)        
        messageLineEdit.forceActiveFocus()
        show();
    }
}

