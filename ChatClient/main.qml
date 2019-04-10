import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import ChatWindow 1.0

import "./res"

ApplicationWindow {
    title: "Chat Room"
    width: 800
    height: 600
    visible: true
    id: root
    color: "#E6E6E6"
    minimumHeight: 300
    minimumWidth: 400    

    property int showWindow: 0
    signal sendButtonClicked

    menuBar: MenuBar{
        Menu{
            visible: showWindow === 2 ? true : false
            title: "File"
            MenuItem
            {   text: "Change Nickname"
                shortcut: "CTRL+N"
                onTriggered:
                {        
                    cmw.popupTitle = "Set Nickname"
                    cmw.changingUser = true;
                    showWindow = 1
                    nameWindow.focusInputName()                    
                }
            }
            MenuItem
            {   text: "Quit"
                shortcut: "CTRL+Q"
                onTriggered: root.close()
            }
        }

        Menu{
            visible: showWindow === 2 ? true : false
            title: "Help"
            MenuItem {text: "About Qt.."}
        }
    }

    Connections{
        target: cmw        
        onOpenPrivateWindow: chatWindow.createPrivateWindow(other)        
        onWindowChanged:{
            showWindow = wind            
            if(wind == 1)  nameWindow.focusInputName()
            if(wind == 2)  chatWindow.focusLineEdit()
        }
    }

    ConnectToServer
    {
        id: connecting
        visible: showWindow == 0 ? true : false
        onCancelPressed: root.close()
        onTryConnectPressed: cmw.clientConnect(ipAddress, m_port)
    }

    Nickname
    {
        id: nameWindow
        visible: showWindow == 1 ? true : false
        Component.onCompleted: focusInputName()
        onCancelButtonPressed: cmw.nickname != "" ? showWindow = 2 : root.close()
        onSetButtonPressed: cmw.sendCommand(ChatWindow.Validate, nameInput)
        setOrTryAgain: cmw.popupTitle
    }

    ChatMainWindow
    {
        id: chatWindow
        visible: showWindow === 2 ? true : false
        onSendButtonPressed: cmw.sendCommand(ChatWindow.Message, cmw.nickname + '\n' + lineMessages)
        onOpenPM: cmw.sendCommand(ChatWindow.OpenPmWindow, nickname2)
        onAlertWindow: root.alert(0)
    }

    Disconnected
    {
        id: connectWindow
        visible: showWindow == 3 ? true : false
        onCancelReconnectPressed: root.close()
        onTryReconnectPressed: cmw.reconnect()
    }
}
