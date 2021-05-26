import QtQuick 2.0

Rectangle {
    id: base

    color: "transparent"
    width: 266
    height: 248

    property int value: 99

    onValueChanged: {
        if(value > 0)
        {
            img.source = "qrc:/image/nozzle_up2.png"
            label.text = value.toString()
        }
        else if(value < 0)
        {
            img.source = "qrc:/image/nozzle_down2.png"
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
        source: "/image/nozzle_up2.png"
        sourceSize.width: width
        sourceSize.height: height
    }

    Rectangle {
        color: "transparent"
        height: 60
        width: parent.width
        anchors { bottom: parent.bottom }
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
