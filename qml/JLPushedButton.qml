import QtQuick 2.0

Rectangle {
    id: base

    property bool isPressed: false
    property bool enable: true
    property alias text: title.text
    property alias font: title.font
    property int index: 0
    property int borderWidth: 0
    property color borderColor: color

    color: "#ff630b"
    radius: 20

    signal click(int index)

    onBorderWidthChanged: {
        base.border.width = borderWidth
    }

    onBorderColorChanged: {
        base.border.color = borderColor
    }

    onIsPressedChanged: {
        if(enable == true)
        {
            if(isPressed == true)
                color = "#ff630b"
            else
                color = "#2d2c2b"
        }
        else
        {
            color = "#000000"
        }
    }

    onEnableChanged: {
        if(enable == false)
        {
            color = "#000000"
        }
        else
        {
            if(enable == true)
            {
                if(isPressed == true)
                    color = "#ff630b"
                else
                    color = "#2d2c2b"
            }
            else
            {
                color = "#000000"
            }
        }

    }

    Text {
        id: title
        text: "Text"
        anchors.centerIn: parent
        color: "#ffffff"
        font { family: "barlow"; pixelSize: 28; bold: true }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(base.enable == true)
                base.click(base.index)
        }
    }
}
