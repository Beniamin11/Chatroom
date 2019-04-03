import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2

Item
{
    id: chatWindow
    anchors.fill: parent

    signal sendButtonPressed
    signal openPM(string nickname2)

    property string lineMessages: messageLineEdit.text    
    property variant component: Qt.createComponent("PrivateMessage.qml")

    function focusLineEdit()
    {
        messageLineEdit.forceActiveFocus()
    }

    function createPrivateWindow(other) {
        console.log("Create Component Private Window")
        cmw.otherUser = other
        var pmInstance
        pmInstance = component.createObject(chatWindow)
    }

    Connections {
        target: cmw.content
        onRowAdd: chatContent.positionViewAtEnd()
    }

    Rectangle
    {
        id: chatroom
        anchors { left: chatWindow.left; top: chatWindow.top; bottom: messageLineEdit.top; leftMargin: 8;
                  rightMargin: 8; topMargin: 10; bottomMargin: 10;  right: users.left }
        color: "#FFFFFF"
        border { width: 1; color: "lightblue" }

        property bool scrollEnabled: chatContent.contentHeight > chatContent.height
        property bool scrollUpEnabled: scrollEnabled && (chatContent.contentY > chatContent.y )
        property bool scrollDownEnabled: scrollEnabled && ( chatContent.contentY < chatContent.contentHeight - chatContent.height )
        property real windowDimension: parent.height + parent.width
        property int fontSize: if(windowDimension < 850)        return 12
                               else if(windowDimension > 2000 ) return 20
                                    else                        return 16        

        ListView {
            id: chatContent
            anchors { fill: parent; topMargin: 10; bottomMargin: 10; leftMargin: 10}
            model: cmw.content
            clip: true
            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.StopAtBounds
            delegate: TextEdit{
                    x: time.width
                    id: chatText                    
                    font {
                        pixelSize: cmw.content.getAction(index) ? chatroom.fontSize - 1 : chatroom.fontSize
                        family: "TimesNewRoman"
                        bold: cmw.content.getAction(index) ? true : false
                    }
                    text: lineMessage
                    readOnly: true                    
                    color: cmw.content.getColor(index)
                    selectByMouse: true
                    mouseSelectionMode: TextInput.SelectCharacters
                    textFormat: Text.PlainText
                    width: chatContent.width - 85
                    wrapMode: Text.Wrap

                    TextEdit {
                        id: time
                        x: -width
                        font { pixelSize: chatroom.fontSize; family: "TimesNewRoman" }
                        text: timeStamp
                        readOnly: true
                        color: "#000000"
                        selectByMouse: true
                        textFormat: Text.PlainText
                        width: 60
                        wrapMode: Text.Wrap
                    }
                }
            ScrollBar {}
        }
    }

    TextArea
    {
        function send() { sendButtonPressed(); text = ""; }

        id: messageLineEdit
        clip: true
        wrapMode: Text.Wrap        
        height: 65
        anchors {
            bottom: chatWindow.bottom
            left: chatWindow.left
            right: chatroom.right
            bottomMargin: 30
            leftMargin: 10
        }
        font { pixelSize: 16; family: "TimesNewRoman"; }
        selectByMouse: true
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

    Rectangle{
        id: users        
        anchors { top: chatroom.top; bottom: chatroom.bottom; right: chatWindow.right;
                  leftMargin: 8; rightMargin: 8}
        width: chatWindow.width / 5.5
        color: "lightyellow"
        border {width: 1; color:"blue"}
        ListView{
            id: userList
            anchors {fill: parent; margins: 3}            
            model: cmw.users
            highlight: highlightbar
            clip: true
            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.StopAtBounds
            delegate: Text{
                id: txtDelegate
                x: 20
                font{ family: "TimesNewRoman"; pixelSize: chatroom.fontSize }
                text: userName
                textFormat: Text.PlainText
                width: parent.width - 20
                height: chatWindow.height / 30
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignHCenter

                Image {
                    id: idCurrent
                    anchors.verticalCenter: txtDelegate.verticalCenter
                    x: -15
                    source: "indicator.png"
                    height: 12
                    width: 12
                    visible: txtDelegate.text == cmw.nickname ? true : false
                }

                MouseArea
                {
                    id: userMouse
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onEntered: {userList.currentIndex = index; userList.currentItem.forceActiveFocus()}
                    onClicked:  if( (mouse.button & Qt.RightButton) && (cmw.nickname !== txtDelegate.text) )
                                     rightClickMenu.popup()
                }
                Menu {
                    id: rightClickMenu
                    __yOffset: userMouse.y; __xOffset: userMouse.x
                    MenuItem{ text: "Private Message"; onTriggered: openPM(txtDelegate.text) }
                }

            }

            Component {
                id: highlightbar
                Rectangle{
                    x: userList.currentItem.x ; y: userList.currentItem.y; color: "#0404B4"; radius: 3
                    height: userList.currentItem.height; width: userList.width ; opacity:0.5 }
            }

            Component.onCompleted: userList.currentIndex = -1
        }
    }

    Button
    {
        id: sendButton
        width: chatWindow.width / 9
        height: 30
        anchors { verticalCenter: messageLineEdit.verticalCenter; horizontalCenter: users.horizontalCenter }
        text: "Send"
        enabled: (messageLineEdit.text != "") &&( messageLineEdit.text != " ") ? true : false
        isDefault: true
        onClicked: { sendButtonPressed(); messageLineEdit.text = ""}
    }

}
