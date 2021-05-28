import QtQuick 2.0

Rectangle {
    id: base

    property int indicator: 0
    property bool extruderEnabled: true
    property int temp: 0
    property string distance: "1"

    property int leftTemp: 0
    property int rightTemp: 0
    property string leftDistance: "1"
    property string rightDistance: "1"


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
        if(temp == 0)
            txtTargetTemp.text = "000°C"
        else
            txtTargetTemp.text = temp.toString() + "°C"
        if(indicator == 0)
            leftTemp = temp
        else
            rightTemp = temp
    }

    onDistanceChanged: {
        if(indicator == 0)
            leftDistance = distance
        else
            rightDistance = distance
        txtTargetDistance.text = distance + "mm"
    }

    onIndicatorChanged: {
        if(indicator == 0)
        {
            btnCooldown.source = "/image/left_cooldown.png"
            if(leftTemp == 0)
                txtTargetTemp.text = "000°C"
            else
                txtTargetTemp.text = leftTemp.toString() + "°C"
            distance = leftDistance
        }
        else
        {
            btnCooldown.source = "/image/right_cooldown.png"
            if(rightTemp == 0)
                txtTargetTemp.text = "000°C"
            else
                txtTargetTemp.text = rightTemp.toString() + "°C"
            distance = rightDistance
        }
    }

    onExtruderEnabledChanged: {
        if(extruderEnabled == true) {
            btnLoad.enable = true
            btnUnload.enable = true
        }
        else {
            btnLoad.enable = false
            btnUnload.enable = false
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
        color: "#ff630b"

        Text {
            id: txtTargetTemp
            anchors.centerIn: parent
            // width: 120
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
        color: "#ff630b"

        Text {
            id: txtTargetDistance
            anchors.centerIn: parent
            // width: 120
            height: 58
            text: "1mm"
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

    JLIconButton {
        id: btnLoad
        x: 904
        y: 39
        width: 140
        height: 140
        icon: "qrc:/image/load_enable.png"
        pressedIcon: "qrc:/image/load_pressed.png"
        disableIcon: "qrc:/image/load_disable.png"
        onRelease: {
            base.extrudeClicked(base.indicator);
        }
    }

    JLIconButton {
        id: btnUnload
        x: 596
        y: 39
        width: 140
        height: 140
        icon: "qrc:/image/unload_enable.png"
        pressedIcon: "qrc:/image/unload_pressed.png"
        disableIcon: "qrc:/image/unload_disable.png"
        onRelease: {
            base.retractClicked(base.indicator);
        }
    }
}
