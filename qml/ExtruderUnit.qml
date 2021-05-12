import QtQuick 2.0

Rectangle {
    id: base

    property int indicator: 0
    property bool extruderEnabled: false
    property int temp: 0
    property alias distance: txtTargetDistance.text


    width: 1094
    height: 513
    color: "#2d2b2c"
    radius: 20

    signal cooldownClicked(int Indicator)
    signal extrudeClicked(int Indicator)
    signal retractClicked(int Indicator)
    signal chooseTempClicked(int Indicator)
    signal chooseDistanceClicked(int Indicator)

    onTempChanged: {
        txtTargetTemp.text = temp.toString() + "°C"
    }

    onIndicatorChanged: {
        if(indicator == 0)
            btnCooldown.source = "/image/left_cooldown.png"
        else
            btnCooldown.source = "/image/right_cooldown.png"
    }

    onExtruderEnabledChanged: {
        if(extruderEnabled == true) {
            btnExtrude.source = "/image/extrude_enable.png"
            btnRetract.source = "/image/retract_enable.png"
        }
        else {
            btnExtrude.source = "/image/extrude_disenable.png"
            btnRetract.source = "/image/retract_disenable.png"
        }
    }

    Image {
        anchors.fill: parent
        source: "/image/extruder_bg.png"
        sourceSize.height: height
        sourceSize.width: width
    }

    Rectangle {
        x: 278
        y: 76

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
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.chooseTempClicked(base.indicator)
            }
        }
    }

    Rectangle {
        x: 278
        y: 248
        width: 220
        height: 72
        radius: 8
        color: "#ff930b"

        Text {
            id: txtTargetDistance
            x: 39
            y: 15
            width: 120
            height: 58
            text: "0.1mm"
            font {pixelSize: 36; family: "Barlow"; bold: true}
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.chooseDistanceClicked(base.indicator)
            }
        }
    }

    Image {
        id: btnCooldown
        source: "/image/left_cooldown.png"
        x: 594
        y: 230
        width: 448
        height: 96

        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.cooldownClicked(base.indicator);
            }
        }
    }

    Image {
        id: btnExtrude
        source: "/image/extrude_disable.png"
        x: 904

        y: 39
        width: 140
        height: 140

        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.extrudeClicked(base.indicator);
            }
        }
    }

    Image {
        id: btnRetract
        source: "/image/retract_disable.png"
        x: 596
        y: 39
        width: 140
        height: 140

        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.extrudeClicked(base.indicator);
            }
        }
    }
}
