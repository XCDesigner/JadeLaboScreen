import QtQuick 2.0

Rectangle {
    id: base

    property bool isPressed: false
    property bool enable: true
    property alias text: title.text
    property alias font: title.font
    property int index: 0

    //property alias borderWidth: base.border.width
    //property alias borderColor: base.border.color
    color: "#2d2c2b"
    radius: 20

    signal clicked(int index)

    function setBorder(width: int, color)
    {
        base.border.width = width
        base.border.color = color
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
        anchors.centerIn: parent
        color: "#ffffff"
        font { family: "barlow"; pixelSize: 28; bold: true }
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            if(base.enable == true)
                base.clicked(base.index)
        }
    }
}
