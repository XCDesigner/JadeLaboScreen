import QtQuick 2.0

Rectangle {
    id: base
    property bool enable: true

    width: 120
    height: 60
    color: "transparent"

    onEnableChanged: {
        if(base.enable === true) {
            switchCircle.x = 0
            background.color = "#ffffff"
        }
        else {
            switchCircle.x = base.width - switchCircle.width
            background.color = "#606060"
        }
    }

    Rectangle {
        id: background
        color: "#ffffff"
        x: switchCircle.radius - radius
        y: base.height / 2 - radius
        width: base.width - (switchCircle.radius - radius) * 2
        height: radius * 2
        radius: 22
    }

    Rectangle {
        id: switchCircle
        x: 0
        y: 0
        width: base.height
        height: base.height
        radius: base.height / 2
        color: "#F9630B"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(base.enable == true) {
                    base.enable = false
                }
                else if(base.enable == false) {
                    base.enable = true
                }

            }
        }
    }
}
