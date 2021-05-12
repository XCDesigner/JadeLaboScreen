import QtQuick 2.0

Rectangle {
    id: base

    width: 534
    height: 336

    radius: 20
    color: "#2d2c2b"

    signal choseTempClicked()

    Image {
        anchors.fill: parent
        source: "/image/left_heating_bg.png"
    }

    Rectangle {
        x: 278
        y: 100
        width: 220
        height: 72
        radius: 8
        color: "#ff930b"

        Text {
            id: txtTargetTemp
            x: 39
            y: 15
            width: 120
            height: 58
            text: "000°C"
            font {pixelSize: 36; family: "Barlow"; bold: true}
            horizontalAlignment: Text.AlignLeft
            color: "#ffffff"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.choseTempClicked()
            }
        }
    }


}
