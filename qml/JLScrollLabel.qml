import QtQuick 2.0

Rectangle {
    id: base
    property alias text: label.text
    width: 600
    height: 80
    color: "transparent"

    onTextChanged: {
        if(label.advance.width > 300) {
            label.x = 0
            tmr.running = true
        }
        else {
            label.x = 0
            tmr.running = false
        }
    }

    Timer {
        id: tmr
        running: false
        repeat: true
        interval: 200
        onTriggered: {
            if(tmr.running == true)
                label.x = label.x - 5
            if(label.x <= -label.advance.width)
                label.x = 0
        }
    }

    Text {
        id: label
        x: 0
        y: 0
        verticalAlignment: Text.AlignVCenter
        font { family: "barlow"; pixelSize: 48; bold: true }
        height: parent.height
        width: parent.width
        color: "white"
        text: "FilaName"
    }

}
