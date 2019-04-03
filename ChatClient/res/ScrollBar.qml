import QtQuick 2.0;

Item {
    id: scrollbar;
    width: 8
    visible: (flickable.visibleArea.heightRatio < 1.0);
    anchors {
        top: flickable.top;
        right: flickable.right;
        bottom: flickable.bottom;
        rightMargin: 5;
    }

   property Flickable flickable: parent;

   Binding {
        target: handle;
        property: "y";
        value: {
//            console.log("HANDLE cY: " + flickable.contentY +  " |cH: " + flickable.contentHeight ) // |maxY: " + clicker.drag.maximumY +
//                        " |cH: " + flickable.contentHeight + " |h: " + flickable.height + " |y: " + handle.y)
            return (flickable.contentY * clicker.drag.maximumY / (flickable.contentHeight - flickable.height)) ;
        }
        when: (!clicker.drag.active);
    }

    Binding {
        target: flickable;
        property: "contentY";
        value:{
//            console.log( "cY: " + flickable.contentY + " |maxY: " + clicker.drag.maximumY + " |cH: " + flickable.contentHeight + " |h: "
//                        + flickable.height + " |hh:" + handle.height + " |hR: " + flickable.visibleArea.heightRatio)
            return (handle.y * (flickable.contentHeight - flickable.height) / clicker.drag.maximumY);
        }
        when: (clicker.drag.active || clicker.pressed);
    }

    Rectangle {
        id: backScrollbar;
        radius: width/2 - 1;
        antialiasing: true;
        color: "#A9D0F5"
        anchors { fill: parent; }

        MouseArea {
            anchors.fill: parent;
            onClicked: { }
        }
    }

    Item {
        id: groove;
        clip: true;
        anchors.fill: parent

        MouseArea {
            id: clicker;
            drag {
                target: handle;
                minimumY: 0;
                maximumY: (groove.height - handle.height);
                axis: Drag.YAxis;
            }
            anchors { fill: parent; }
            onClicked: { flickable.contentY = (mouse.y / groove.height * (flickable.contentHeight - flickable.height)); }
        }
        Item {
            id: handle;
            height: Math.max (flickable.visibleArea.heightRatio * groove.height);
            anchors {
                left: parent.left;
                right: parent.right;
            }

            Rectangle {
                id: backHandle;
                radius: width/2 - 1
                color: (clicker.pressed ? "blue" : "#0B173B");
                opacity: (flickable.moving ? 0.65 : 0.35);
                anchors { fill: parent; }

                Behavior on opacity { NumberAnimation { duration: 150; } }
            }
        }
    }
}
