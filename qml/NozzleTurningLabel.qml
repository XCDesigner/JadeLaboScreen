import QtQuick 2.0

Rectangle {
    id: base

    color: "transparent"
    width: 260
    height: 246

    property int value: 99

    onValueChanged: {
        if(value > 0)
        {
            img.source = "qrc:/image/nozzle_up.png"
            label.text = value.toString()
        }
        else if(value < 0)
        {
            img.source = "qrc:/image/nozzle_down.png"
            label.text = (-value).toString()
        }
        else
        {
            img.source = ""
            label.text = value.toString()
        }
    }

    Image {
        id: img
        anchors.fill: parent
        source: "/image/nozzle_up.png"
        sourceSize.width: width
        sourceSize.height: height
    }

    Rectangle {
        color: "transparent"
        height: parent.height
        width: 60
        anchors { left: parent.left }
        Text {
            id: label
            text: "3"
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
            color: "white"
            font { family: "barlow"; pixelSize: 42; bold: true }
        }
    }
}
