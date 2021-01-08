import QtQuick 2.0

Item {
    id: contextButtonItem
    property string button_text;
    property bool clicked;
    property int index;
    property string target;
    property bool enable: true;
    signal buttonClicked;
    height: 25
    width: parent.width - 5

    function viewButtonHovered() {
        viewButton.state = "hovered";
        outerArea.z= -10;
    }

    function viewButtonExited() {
        outerArea.z= 1;
        if(clicked == false) {
            viewButton.state = "";
        } else {
            viewButton.state = "clicked"
        }
    }
    Rectangle {
        id: viewButton;
        height: vButton.height + 4
        width: parent.width

        Text {
            id: vButton
            text: qsTr(button_text)
            width: parent.width
            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
            font { pixelSize: 14 }
        }
        MouseArea {
            hoverEnabled: enable
            anchors.fill: parent
            enabled: enable
            onClicked: buttonClicked();
            onEntered: viewButtonHovered();
            onExited: viewButtonExited();
        }
        states: [
            State {
                name: "clicked";
                PropertyChanges { target: vButton; color: "#286E1E"; }
            },
            State {
                name: "hovered";
                PropertyChanges { target: vButton; color: "#BEA1C6"; }
            },
            State {
                name: "normal";
                PropertyChanges { target: vButton; color: "#232323"; }
            }
        ]
    }
}
