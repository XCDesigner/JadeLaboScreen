import QtQuick 2.0

Rectangle {
    id: base

    property int value;

    width: 1080
    height: 270
    radius: 20
    color: "#2d2c2b"

    signal choseTempClicked()
    signal cooldownClicked()

    onValueChanged: {
        if(value == 0)
            txtTargetTemp.text = "000°C"
        else
            txtTargetTemp.text = value.toString() + "°C"
    }

    Image {
        id: background
        anchors.fill: parent
        source: "qrc:/image/bed_heating_bg.png"
    }

    Rectangle {
        x: 278
        y: 145
        width: 220
        height: 72
        radius: 8
        color: "#ff630b"

        Text {
            id: txtTargetTemp
            anchors.centerIn: parent
            //width: 120
            //height: 58
            text: "000°C"
            font {pixelSize: 36; family: "Barlow"; bold: true}
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.choseTempClicked()
            }
        }
    }

    Image {
        id: btnCooldown
        source: "/image/bed_cooldown.png"
        x: 582
        y: 122
        width: 464
        height: 96

        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.cooldownClicked();
            }
        }
    }


}
