import QtQuick 2.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.15

// main window
Window {	
    visible: true
    width: 720
    height: 720

    Rectangle {
        color: "#373737"
        border.color: "#535353"
        anchors.fill: parent

        Row {
            id: row
            anchors.fill: parent

            Rectangle {
                id: topBar
                color: "#1a000000"
                border.color: "#1affffff"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: 100

                Text {
                    id: title
                    x: 44
                    color: "#d5d5d5"
                    text: qsTr("Quester")
                    anchors.top: parent.top
                    font.pixelSize: 24
                    anchors.topMargin: 25
                    font.family: "Verdana"
                }

                Text {
                    id: subtitile
                    height: 17
                    color: "#d5d5d5"
                    text: qsTr("Select Project")
                    anchors.left: title.horizontalCenter
                    anchors.right: title.right
                    anchors.top: title.bottom
                    font.pixelSize: 14
                    anchors.leftMargin: -20
                    anchors.rightMargin: 0
                    font.family: "Verdana"
                    anchors.topMargin: 6
                }
            }

            Flow {
                id: flow1
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: topBar.bottom
                anchors.bottom: parent.bottom
                spacing: 10
                anchors.rightMargin: 20
                anchors.leftMargin: 20
                anchors.bottomMargin: 10
                anchors.topMargin: 10


                Rectangle {
                    id: addNew
                    width: 90
                    height: 110
                    color: "#26ffffff"
                    radius: 3
                    Text {
                        color: "#d5d5d5"
                        anchors.centerIn: parent
                        text: "+"
                        font.pointSize: 24
                        font.family: "Verdana"
                    }
                    MouseArea {
                        anchors.fill: addNew
                        hoverEnabled: true
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        onClicked: {
                            Qt.quit();
                        }
                        onEntered: {
                            addNew.opacity = .5
                        }
                        onExited: {
                            addNew.opacity = 1
                        }
                    }

                    ColorAnimation {
                        id: colorAnimation
                        from: "#26ffffff"
                        to: "green"
                    }
                    function containsMouse(item) {
                        var relativePos = globalMouseArea.mapToItem(item, globalMouseArea.mouseX, globalMouseArea.mouseY);
                        return item.contains(Qt.point(relativePos.x, relativePos.y));
                    }
                }

                Rectangle {
                    id: testProject
                    color: "#26ffffff"
                    radius: 3
                    width: childrenRect.width + 20
                    height: 110
                    Text {
                        id: pTitle
                        color: "#d5d5d5"
                        text: "Test Project 1"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.leftMargin: 10
                        font.pointSize: 12
                        font.family: "Verdana"
                    }

                    Text {
                        color: "#d5d5d5"
                        text: "Test Project 1"
                        anchors.bottom: pTitle.verticalCenter
                        anchors.bottomMargin: -45
                        font.pointSize: 12
                        font.family: "Verdana"
                    }

                    MouseArea {
                        anchors.fill: testProject
                        hoverEnabled: true
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                    }

                    ColorAnimation {
                        id: colorAnimation1
                        to: "#008000"
                        from: "#26ffffff"
                    }

                }
            }

        }
    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:4}D{i:7}D{i:11}D{i:6}D{i:2}
}
##^##*/
