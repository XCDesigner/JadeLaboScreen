import QtQuick 2.0

Rectangle {
    id: base

    property url icon: ""
    property url pressedIcon: ""

    property bool isPressed: false

    radius: 20

    signal press()
    signal release()

    onIsPressedChanged: {
        if(isPressed == true)
            img.source = pressedIcon
        else
            img.source = icon
    }

    Image {
        id: img
        anchors.fill: parent
        sourceSize.height: height
        sourceSize.width: width
    }

    MouseArea{
        anchors.fill: parent
        onReleased: {
            base.isPressed = false
            base.release()
        }
        onPressed: {
            base.isPressed = true
            base.press()
        }
    }

}
