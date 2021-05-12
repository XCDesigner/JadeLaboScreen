import QtQuick 2.0

Rectangle {
    id: base

    property int unitIndicator: 0
    property int value;

    width: 534
    height: 336
    radius: 20
    color: "#2d2c2b"

    signal choseTempClicked(int Indicator)
    signal cooldownClicked(int Indicator)

    onValueChanged: {
        if(value == 0)
            txtTargetTemp.text = "000°C"
        else
            txtTargetTemp.text = value.toString() + "°C"
    }

    onUnitIndicatorChanged: {
        if(unitIndicator == 0)
        {
            background.source = "/image/left_heating_bg.png"
            btnCooldown.source = "/image/left_cooldown.png"
        }
        else if(unitIndicator == 1)
        {
            background.source = "/image/right_heating_bg.png"
            btnCooldown.source = "/image/right_cooldown.png"
        }
    }

    Image {
        id: background
        anchors.fill: parent
        source: "qrc:/image/left_heating_bg.png"
    }

    Rectangle {
        x: 278
        y: 100
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
                base.choseTempClicked(base.unitIndicator)
            }
        }
    }

    Image {
        id: btnCooldown
        source: "qrc:/image/left_cooldown.png"
        x: 38
        y: 207
        width: 464
        height: 96

        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.cooldownClicked(base.unitIndicator);
            }
        }
    }


}
