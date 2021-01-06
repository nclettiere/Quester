import QtQuick 2.0

Item {
    Rectangle {
        id: rectangle
        color: "#202020"
        anchors.fill: parent
    }

    Row {
        id: row
        anchors.fill: parent
    }

    Text {
        id: text1
        text: qsTr("Select Project")
        font.pixelSize: 48
        font.family: "Verdana"
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1}D{i:2}
}
##^##*/
