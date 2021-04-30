import QtQuick 2.0

Rectangle {
    id: base

    property url icon: ""
    property url pressedIcon: ""
    property url disableIcon: ""

    property bool isPressed: false
    property bool enable: true

    radius: 20
    color: "#202020"

    signal press()
    signal release()

    onEnableChanged: {
        if(enable == true)
        {
            img.source = icon
        }
        else
        {
            img.source = disableIcon
            isPressed = false
        }
    }

    onIsPressedChanged: {
        if(enable == true)
        {
            if(isPressed == true)
                img.source = pressedIcon
            else
                img.source = icon
        }
    }

    Image {
        id: img
        source: base.icon
        anchors.fill: parent
        sourceSize.height: height
        sourceSize.width: width
    }

    MouseArea{
        anchors.fill: parent
        onReleased: {
            if(base.enable == true)
            {
                base.isPressed = false
                base.release()
            }
        }
        onPressed: {
            if(base.enable == true)
            {
                base.isPressed = true
                base.press()
            }
        }
    }

}
