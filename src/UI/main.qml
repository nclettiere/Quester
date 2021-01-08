import QtQuick 2.3
import QtQuick.Controls 2.15
import QtQuick.Window 2.2
import QtGraphicalEffects 1.15

// main window
ApplicationWindow {
    id: root
    visible: true
    width: 642
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
                            var component = Qt.createComponent("ProjectCreatorWindow.qml")
                            var window    = component.createObject(root)
                            window.show()
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
                    width: 245
                    height: 110

                    MouseArea {
                        anchors.fill: testProject
                        hoverEnabled: true
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        onClicked: {
                            if(mouse.button == Qt.RightButton) {
                                popup.x = mouse.x
                                popup.y = mouse.y
                                popup.open()
                            }else {
                                Qt.quit()
                            }
                        }
                        onEntered: {
                            testProject.opacity = .5
                        }
                        onExited: {
                            testProject.opacity = 1
                        }
                    }
                    Popup {
                        id: popup
                        modal: false
                        focus: false
                        width: 200
                        height: ctxContent.height + 20
                        rightPadding: 0
                        bottomPadding: 0
                        topPadding: 0
                        leftPadding: 0
                        rightMargin: 0
                        bottomMargin: 0
                        leftMargin: 0
                        topMargin: 0
                        clip: true
                        dim: false
                        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

                        Rectangle {
                            id: ctxContent
                            color: "#e6000000"
                            anchors.fill: parent
                            anchors.rightMargin: 1
                            anchors.leftMargin: 1
                            anchors.bottomMargin: 1
                            anchors.topMargin: 1
                            height: 85

                            Column {
                                anchors.fill: parent
                                id: column4
                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        anchors.fill: parent
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Quick Export"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            font.pointSize: 10
                                            anchors.horizontalCenter: parent.horizontalCenter
                                        }
                                    }
                                }

                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        anchors.fill: parent
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Duplicate"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            font.pointSize: 10
                                            anchors.horizontalCenter: parent.horizontalCenter
                                        }
                                    }
                                }

                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        anchors.fill: parent
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Delete"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            font.pointSize: 10
                                            anchors.horizontalCenter: parent.horizontalCenter
                                        }
                                    }
                                }
                            }
                        }
                    }
                    function getAbsolutePosition(node) {
                        var returnPos = {};
                        returnPos.x = 0;
                        returnPos.y = 0;
                        if(node !== undefined && node !== null) {
                            var parentValue = getAbsolutePosition(node.parent);
                            returnPos.x = parentValue.x + node.x;
                            returnPos.y = parentValue.y + node.y;
                        }
                        return returnPos;
                    }
                    Column {
                        id: column
                        anchors.fill: parent

                        Text {
                            id: text2
                            color: "#d5d5d5"
                            text: qsTr("Default Project")
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.verticalCenter
                            anchors.bottom: rectangle.top
                            font.pixelSize: 21
                            horizontalAlignment: Text.AlignHCenter
                            wrapMode: Text.WrapAnywhere
                            anchors.topMargin: -15
                            anchors.bottomMargin: -20
                        }

                        Rectangle {
                            id: rectangle
                            color: "#26ffffff"
                            radius: 3
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.leftMargin: 0
                            anchors.rightMargin: 0
                            anchors.bottomMargin: 0
                            height: 20

                            Text {
                                id: text1
                                color: "#d5d5d5"
                                text: qsTr("C:\\Users\\Percebe64\\Documents\\Projects\\q\\...")
                                elide: Text.ElideRight
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                font.pixelSize: 10
                                wrapMode: Text.WrapAnywhere
                                fontSizeMode: Text.FixedSize
                                renderType: Text.QtRendering
                                minimumPixelSize: 12
                                anchors.leftMargin: 10
                            }
                        }

                    }

                    MouseArea {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        hoverEnabled: true
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                    }

                    ColorAnimation {
                        id: colorAnimation1
                        to: "#008000"
                        from: "#26ffffff"
                    }



                }

                Rectangle {
                    id: testProject1
                    width: 245
                    height: 110
                    color: "#26ffffff"
                    radius: 3
                    MouseArea {
                        anchors.fill: testProject1
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        hoverEnabled: true
                    }

                    Popup {
                        id: popup1
                        width: 200
                        height: ctxContent1.height + 20
                        modal: false
                        dim: false
                        clip: true
                        bottomMargin: 0
                        topPadding: 0
                        bottomPadding: 0
                        leftPadding: 0
                        Rectangle {
                            id: ctxContent1
                            height: 85
                            color: "#e6000000"
                            anchors.fill: parent
                            anchors.leftMargin: 1
                            Column {
                                id: column5
                                anchors.fill: parent
                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        anchors.fill: parent
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Quick Export"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.pointSize: 10
                                        }
                                    }
                                }

                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        anchors.fill: parent
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Duplicate"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.pointSize: 10
                                        }
                                    }
                                }

                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        anchors.fill: parent
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Delete"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.pointSize: 10
                                        }
                                    }
                                }
                            }
                            anchors.topMargin: 1
                            anchors.rightMargin: 1
                            anchors.bottomMargin: 1
                        }
                        topMargin: 0
                        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                        focus: false
                        rightMargin: 0
                        rightPadding: 0
                        leftMargin: 0
                    }

                    Column {
                        id: column1
                        anchors.fill: parent
                        Text {
                            id: text3
                            color: "#d5d5d5"
                            text: qsTr("Default Project")
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.verticalCenter
                            anchors.bottom: rectangle1.top
                            font.pixelSize: 21
                            horizontalAlignment: Text.AlignHCenter
                            wrapMode: Text.WrapAnywhere
                            anchors.topMargin: -15
                            anchors.bottomMargin: -20
                        }

                        Rectangle {
                            id: rectangle1
                            height: 20
                            color: "#26ffffff"
                            radius: 3
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.leftMargin: 0
                            Text {
                                id: text4
                                color: "#d5d5d5"
                                text: qsTr("C:\\Users\\Percebe64\\Documents\\Projects\\q\\...")
                                elide: Text.ElideRight
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                font.pixelSize: 10
                                wrapMode: Text.WrapAnywhere
                                renderType: Text.QtRendering
                                anchors.leftMargin: 10
                                minimumPixelSize: 12
                                fontSizeMode: Text.FixedSize
                            }
                            anchors.rightMargin: 0
                            anchors.bottomMargin: 0
                        }
                    }

                    MouseArea {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        hoverEnabled: true
                    }

                    ColorAnimation {
                        id: colorAnimation2
                        to: "#008000"
                        from: "#26ffffff"
                    }
                }

                Rectangle {
                    id: testProject2
                    width: 245
                    height: 110
                    color: "#26ffffff"
                    radius: 3
                    MouseArea {
                        anchors.fill: testProject2
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        hoverEnabled: true
                    }

                    Popup {
                        id: popup2
                        width: 200
                        height: ctxContent2.height + 20
                        modal: false
                        dim: false
                        clip: true
                        bottomMargin: 0
                        topPadding: 0
                        bottomPadding: 0
                        leftPadding: 0
                        Rectangle {
                            id: ctxContent2
                            height: 85
                            color: "#e6000000"
                            anchors.fill: parent
                            anchors.leftMargin: 1
                            Column {
                                id: column6
                                anchors.fill: parent
                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        anchors.fill: parent
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Quick Export"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.pointSize: 10
                                        }
                                    }
                                }

                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        anchors.fill: parent
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Duplicate"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.pointSize: 10
                                        }
                                    }
                                }

                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        anchors.fill: parent
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Delete"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.pointSize: 10
                                        }
                                    }
                                }
                            }
                            anchors.topMargin: 1
                            anchors.rightMargin: 1
                            anchors.bottomMargin: 1
                        }
                        topMargin: 0
                        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                        focus: false
                        rightMargin: 0
                        rightPadding: 0
                        leftMargin: 0
                    }

                    Column {
                        id: column2
                        anchors.fill: parent
                        Text {
                            id: text5
                            color: "#d5d5d5"
                            text: qsTr("Default Project")
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.verticalCenter
                            anchors.bottom: rectangle2.top
                            font.pixelSize: 21
                            horizontalAlignment: Text.AlignHCenter
                            wrapMode: Text.WrapAnywhere
                            anchors.topMargin: -15
                            anchors.bottomMargin: -20
                        }

                        Rectangle {
                            id: rectangle2
                            height: 20
                            color: "#26ffffff"
                            radius: 3
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.leftMargin: 0
                            Text {
                                id: text6
                                color: "#d5d5d5"
                                text: qsTr("C:\\Users\\Percebe64\\Documents\\Projects\\q\\...")
                                elide: Text.ElideRight
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                font.pixelSize: 10
                                wrapMode: Text.WrapAnywhere
                                renderType: Text.QtRendering
                                anchors.leftMargin: 10
                                minimumPixelSize: 12
                                fontSizeMode: Text.FixedSize
                            }
                            anchors.rightMargin: 0
                            anchors.bottomMargin: 0
                        }
                    }

                    MouseArea {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        hoverEnabled: true
                    }

                    ColorAnimation {
                        id: colorAnimation3
                        to: "#008000"
                        from: "#26ffffff"
                    }
                }

                Rectangle {
                    id: testProject3
                    width: 245
                    height: 110
                    color: "#26ffffff"
                    radius: 3
                    MouseArea {
                        anchors.fill: testProject3
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        hoverEnabled: true
                    }

                    Popup {
                        id: popup3
                        width: 200
                        height: ctxContent3.height + 20
                        modal: false
                        dim: false
                        clip: true
                        bottomMargin: 0
                        topPadding: 0
                        bottomPadding: 0
                        leftPadding: 0
                        Rectangle {
                            id: ctxContent3
                            height: 85
                            color: "#e6000000"
                            anchors.fill: parent
                            anchors.leftMargin: 1
                            Column {
                                id: column7
                                anchors.fill: parent
                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        anchors.fill: parent
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Quick Export"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.pointSize: 10
                                        }
                                    }
                                }

                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        anchors.fill: parent
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Duplicate"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.pointSize: 10
                                        }
                                    }
                                }

                                Button {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    Rectangle {
                                        color: "#cc000000"
                                        border.color: "#3b3b3b"
                                        anchors.fill: parent
                                        Text {
                                            color: "#a4a4a4"
                                            text: "Delete"
                                            anchors.verticalCenter: parent.verticalCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            font.pointSize: 10
                                        }
                                    }
                                }
                            }
                            anchors.topMargin: 1
                            anchors.rightMargin: 1
                            anchors.bottomMargin: 1
                        }
                        topMargin: 0
                        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                        focus: false
                        rightMargin: 0
                        rightPadding: 0
                        leftMargin: 0
                    }

                    Column {
                        id: column3
                        anchors.fill: parent
                        Text {
                            id: text7
                            color: "#d5d5d5"
                            text: qsTr("Default Project")
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.verticalCenter
                            anchors.bottom: rectangle3.top
                            font.pixelSize: 21
                            horizontalAlignment: Text.AlignHCenter
                            wrapMode: Text.WrapAnywhere
                            anchors.topMargin: -15
                            anchors.bottomMargin: -20
                        }

                        Rectangle {
                            id: rectangle3
                            height: 20
                            color: "#26ffffff"
                            radius: 3
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.leftMargin: 0
                            Text {
                                id: text8
                                color: "#d5d5d5"
                                text: qsTr("C:\\Users\\Percebe64\\Documents\\Projects\\q\\...")
                                elide: Text.ElideRight
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                font.pixelSize: 10
                                wrapMode: Text.WrapAnywhere
                                renderType: Text.QtRendering
                                anchors.leftMargin: 10
                                minimumPixelSize: 12
                                fontSizeMode: Text.FixedSize
                            }
                            anchors.rightMargin: 0
                            anchors.bottomMargin: 0
                        }
                    }

                    MouseArea {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
                        hoverEnabled: true
                    }

                    ColorAnimation {
                        id: colorAnimation4
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
    D{i:0;formeditorZoom:0.75}
}
##^##*/
