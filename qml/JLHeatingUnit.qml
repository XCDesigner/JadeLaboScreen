import QtQuick 2.0

Rectangle {
    id: base
    width: 520
    height: 480

    color: "#2b2c2d"

    property alias indicatorIcon: imgIndicator.source
    property alias indicatorText: txtIndicator.text
    property alias text: txtTargetTemp.text

    signal choseTempClicked()
    signal extruderClicked()
    signal retackClicked()

    Image {
        id: imgIndicator
        x: 28
        y: 29
        width: 36
        height: 42
        source: "qrc:/image/RightHotendIndecator.png"
        sourceSize.width: width
        sourceSize.height: height
    }

    Image {
        x: 8
        y: 219
        width: 500
        height: 20
        source: "qrc:/image/2.png"
        sourceSize.width: width
        sourceSize.height: height
    }

    Image {
        x: 228
        y: 319
        width: 70
        height: 102
        source: "qrc:/image/nozzle.png"
        sourceSize.width: width
        sourceSize.height: height
    }

    Text {
        text: "Preheat:"
        x: 38
        y: 109
        width: 150
        height: 60
        font {pixelSize: 32; family: "Barlow"; bold: true}
        horizontalAlignment: Text.AlignLeft
        color: "#b9b9b9"
    }

    Text {
        id: txtIndicator
        text: "Right "
        x: 98
        y: 19
        width: 250
        height: 58
        font {pixelSize: 36; family: "Barlow"; bold: true}
        horizontalAlignment: Text.AlignLeft
        color: "#969696"
    }

    JLIconButton {
        id: btnRetract
        x: 48
        y: 300
        width: 140
        height: 140
        color: "#ff630b"
        icon: "qrc:/image/UpEnable.png"
        pressedIcon: "qrc:/image/UpActive.png"
        disableIcon: "qrc:/image/UpDisable.png"
        onRelease: {
            base.retackClicked()
        }
    }

    JLIconButton {
        id: btnExtrude
        x: 338
        y: 300
        width: 140
        height: 140
        color: "#ff630b"
        icon: "qrc:/image/DownEnable.png"
        pressedIcon: "qrc:/image/DownActived.png"
        disableIcon: "qrc:/image/DownDisable.png"
        onRelease: {
            base.extruderClicked()
        }
    }

    Rectangle {
        x: 238
        y: 109
        width: 220
        height: 72
        radius: 20
        color: "#ff930b"
        Image {
            x: 170
            y: 20
            width: 32
            height: 36
            sourceSize.width: width
            sourceSize.height: height
            source: "qrc:/image/ChangeTemperature.png"
        }

        Text {
            id: txtTargetTemp
            x: 20
            y: 10
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
