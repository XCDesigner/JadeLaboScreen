import QtQuick 2.0

Item {
    id: base

    property int indicator: 0
    width: 1090
    height: 80

    signal clicked(int Indicator)

    onIndicatorChanged: {
        if(indicator == 0) {
            btnleft.color = "#2d2c2b"
            leftcornet.col = "#2d2c2b"
            btnright.color = "#202020"
            rightcorner.color = "#202020"
            leftlabel.color = "#f0f0f0"
            rightlabel.color = "#8f8f8f"
        }
        else if(indicator == 1) {
            btnleft.color = "#202020"
            leftcornet.col = "#202020"
            btnright.color = "#2d2c2b"
            rightcorner.color = "#2d2c2b"
            leftlabel.color = "#8f8f8f"
            rightlabel.color = "#f0f0f0"
        }
    }

    Rectangle {
        id: btnleft
        x: 20
        y: 0
        width: 525
        height: 80
        color: "#2d2c2b"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.indicator = 0
                base.clicked(0)
            }
        }
        Text {
            id:leftlabel
            anchors.centerIn: parent
            text: "L Hotend"
            color: "#f0f0f0"
            font {family: "barlow"; pixelSize: 48; bold: true}
        }
    }

    Rectangle {
        id: btnright
        x: 545
        y: 0
        width: 525
        height: 80
        color: "#202020"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                base.indicator = 1
                base.clicked(1)
            }
        }
        Text {
            id: rightlabel
            anchors.centerIn: parent
            text: "R Hotend"
            color: "#8f8f8f"
            font {family: "barlow"; pixelSize: 48; bold: true}
        }
    }

    Rectangle {
        id: leftcornet
        radius: 20
        width: 40
        height: 80
        x: 0
        y: 0
        color: "#2d2c2b"
    }

    Rectangle {
        id: rightcorner
        radius: 20
        width: 40
        height: 80
        x: 1050
        y: 0
        color: "#202020"
    }

}
