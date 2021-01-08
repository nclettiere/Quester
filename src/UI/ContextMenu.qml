import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: contextMenuItem
    signal menuSelected(int index) // index{1: Select All, 2: Remove Selected}
    property bool isOpen: false
    width: 150
    height: menuHolder.height + 20
    visible: isOpen
    focus: isOpen
    border { width: 1; color: "#BEC1C6" }

    Column {
        id: menuHolder
        spacing: 1
        width: parent.width
        height: children.height * children.length
        anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 3 }

        Button {
            id: selectedAll
            text: "Select All"
            onClicked: menuSelected(1);
        }

        Button {
            id: removeSelected
            text: "Remove Selected"
            onClicked: menuSelected(2);
        }
    }
}
