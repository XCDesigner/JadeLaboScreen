import QtQuick 2.0

Rectangle {
    id: base

    property string distance: "0.1"

    width: 180
    height: 180

    radius: 20
    border.width: 4
    border.color: "#b9b9b9"
    color: "#2d2b2c"

    signal clicked(string value)

    onDistanceChanged: {
        label.text = distance + "mm"
    }

    Text {
        id: label
        anchors.centerIn: parent
        color: "#f0f0f0"
        font { family: "barlow"; pixelSize: 48; bold: true}
        text: "1mm"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            base.clicked(base.distance)
        }
    }
}
