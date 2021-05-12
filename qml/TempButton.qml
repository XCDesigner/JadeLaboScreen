import QtQuick 2.0

Rectangle {
    id: base

    property int temperature: 0

    width: 180
    height: 180

    radius: 20
    border.width: 4
    border.color: "#b9b9b9"
    color: "#2d2b2c"

    signal clicked(int value)

    onTemperatureChanged: {
        label.text = temperature.toString() + "°C"
    }

    Text {
        id: label
        anchors.centerIn: parent
        color: "#f0f0f0"
        font { family: "barlow"; pixelSize: 32; bold: true}
        text: "0°C"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            base.clicked(base.temperature)
        }
    }
}
