import QtQuick 2.3
import QtQuick.Controls 2.15
import QtQuick.Window 2.2
import QtGraphicalEffects 1.15

// main window
import QtQuick.Controls.Imagine 2.3
ApplicationWindow {
    id: root
    visible: true
    width: 420
    height: 400

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
                height: 50

                Text {
                    id: title
                    x: 44
                    color: "#d5d5d5"
                    text: qsTr("Create New Project")
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    font.pixelSize: 18
                    verticalAlignment: Text.AlignVCenter
                    anchors.bottomMargin: 0
                    anchors.topMargin: 0
                    font.family: "Verdana"
                }
            }

            Column {
                id: column
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: topBar.bottom
                anchors.bottom: parent.bottom
                anchors.rightMargin: 25
                anchors.leftMargin: 25
                anchors.bottomMargin: 25
                anchors.topMargin: 25

                Row {
                    id: row1
                    height: 35
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0

                    Text {
                        id: text1
                        width: 100
                        color: "#d5d5d5"
                        text: qsTr("Project Name")
                        anchors.verticalCenter: textField.verticalCenter
                        font.pixelSize: 12
                    }

                    TextField {
                        id: textField
                        height: 35
                        color: "#d5d5d5"
                        anchors.left: text1.right
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        placeholderTextColor: "#868686"
                        anchors.leftMargin: 15
                        placeholderText: qsTr("Insert Name")

                        background: Rectangle {
                            id: txt_back
                            implicitWidth: 200
                            implicitHeight: 40
                            color: "#64000000"
                            border.color: "#c1c1c1"
                            border.width: 2
                        }
                    }
                }

                Row {
                    id: row2
                    height: 35
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: row1.bottom
                    anchors.topMargin: 10
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    Text {
                        id: text2
                        width: 100
                        color: "#d5d5d5"
                        text: qsTr("Project Path")
                        anchors.verticalCenter: textField1.verticalCenter
                        font.pixelSize: 12
                    }

                    TextField {
                        id: textField1
                        height: 35
                        color: "#d5d5d5"
                        anchors.left: text2.right
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        anchors.leftMargin: 15
                        placeholderText: qsTr("")
                        background: Rectangle {
                            id: txt_back1
                            color: "#64000000"
                            border.color: "#c1c1c1"
                            border.width: 2
                            implicitWidth: 200
                            implicitHeight: 40
                        }
                        placeholderTextColor: "#868686"
                    }
                }

                Row {
                    id: row3
                    height: 41
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: row2.bottom
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    Text {
                        id: text3
                        width: 100
                        color: "#d5d5d5"
                        text: qsTr("Project Description")
                        anchors.verticalCenter: textField2.verticalCenter
                        font.pixelSize: 12
                    }

                    TextArea {
                        id: textArea
                        anchors.left: text3.right
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        anchors.leftMargin: 15
                        color: "#d5d5d5"
                        placeholderText: qsTr("Short Description (optional)")

                        background: Rectangle {
                            id: txt_back2
                            color: "#64000000"
                            border.color: "#c1c1c1"
                            border.width: 2
                            implicitWidth: 200
                            implicitHeight: 40
                        }
                        placeholderTextColor: "#868686"
                    }
                    anchors.topMargin: 10
                }

                Row {
                    id: row4
                    height: 35
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: row3.bottom
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    Text {
                        id: text4
                        width: 100
                        color: "#d5d5d5"
                        text: qsTr("Unreal Version")
                        anchors.verticalCenter: control.verticalCenter
                        font.pixelSize: 12
                    }

                    ComboBox {
                        id: control
                        height: 35
                        anchors.left: text4.right
                        anchors.right: parent.right
                        leftPadding: 10
                        flat: false
                        spacing: 0
                        font.family: "Verdana"
                        font.wordSpacing: 0
                        anchors.rightMargin: 0
                        anchors.leftMargin: 15
                        model: ["4.18", "4.19", "4.20", "4.21", "4.18", "4.22", "4.23", "4.24", "4.25", "4.26"]

                        delegate: ItemDelegate {
                            id: itemDel
                            width: control.width
                            background: Rectangle {
                                color:  itemDel.hovered ? "#333333" : "#64000000"
                            }
                            contentItem: Text {
                                text: modelData
                                color: "#d5d5d5"
                                font: control.font
                                elide: Text.ElideRight
                                verticalAlignment: Text.AlignVCenter
                            }
                            highlighted: control.highlightedIndex === index
                        }

                        indicator: Canvas {
                            id: canvas
                            x: control.width - width - control.rightPadding
                            y: control.topPadding + (control.availableHeight - height) / 2
                            width: 12
                            height: 8
                            contextType: "2d"

                            Connections {
                                target: control
                                function onPressedChanged() { canvas.requestPaint(); }
                            }

                            onPaint: {
                                context.reset();
                                context.moveTo(0, 0);
                                context.lineTo(width, 0);
                                context.lineTo(width / 2, height);
                                context.closePath();
                                context.fillStyle = "#d5d5d5";
                                context.fill();
                            }
                        }

                        contentItem: Text {
                            text: control.displayText
                            font: control.font
                            color: "#d5d5d5"
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            implicitWidth: 120
                            implicitHeight: 40
                            color: "#64000000"
                            border.color: "#c1c1c1"
                            border.width: 2
                            //color: "pink"
                            //border.color: control.pressed ? "blue" : "red"
                            //border.width: control.visualFocus ? 2 : 1
                            //radius: 2
                        }

                        popup: Popup {
                            y: control.height - 1
                            width: control.width
                            implicitHeight: contentItem.implicitHeight
                            padding: 1

                            contentItem: ListView {
                                clip: true
                                implicitHeight: contentHeight
                                model: control.popup.visible ? control.delegateModel : null
                                currentIndex: control.highlightedIndex

                                ScrollIndicator.vertical: ScrollIndicator { }
                            }

                            background: Rectangle {
                                color: "#131313"
                                border.color: "#0f0f0f"
                                radius: 2
                            }
                        }
                    }
                    anchors.topMargin: 10
                }

                Row {
                    id: row5
                    height: 35
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: row4.bottom
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                    Text {
                        id: text5
                        width: 100
                        color: "#d5d5d5"
                        text: qsTr("Include Example Graphs")
                        anchors.verticalCenter: checkBox.verticalCenter
                        font.pixelSize: 12
                        wrapMode: Text.WrapAnywhere
                    }

                    CheckBox {
                        id: checkBox
                        text: qsTr("")
                        anchors.left: text5.right
                        transformOrigin: Item.Center
                        scale: 1
                        clip: true
                        Component.onCompleted: indicator.children[0].color = "green"
                        anchors.leftMargin: 5
                        background: Rectangle {
                            width: 100
                            color: "#68a666"
                            border.color: button.pressed ? "#80000000" : "#33fdfdfd"
                            border.width: 2
                        }
                    }
                    anchors.topMargin: 10
                }

                Button {
                    id: button
                    width: 100
                    height: 35
                    text: qsTr("Create")
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    font.pointSize: 12
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0

                    background: Rectangle {
                        width: 100
                        color: "#68a666"
                        border.color: button.pressed ? "#80000000" : "#33fdfdfd"
                        border.width: 2
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
