import QtQuick 2.0

Rectangle {
    id: base

    color: "transparent"
    width: 190
    height: 190

    property int value: 0

    onValueChanged: {
        if(value > 0)
        {
            img.source = "qrc:/image/turn_dec.png"
            label.text = value.toString()
        }
        else if(value < 0)
        {
            img.source = "qrc:/image/turn_inc.png"
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
        source: "/image/turn_inc.png"
        sourceSize.width: width
        sourceSize.height: height
    }

    Text {
        id: label
        text: "3"
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
        color: "white"
        font { family: "barlow"; pixelSize: 32; bold: true }
    }
}
