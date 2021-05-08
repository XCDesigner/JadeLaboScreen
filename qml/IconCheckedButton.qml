import QtQuick 2.0

Image {
    id: base

    property url icon
    property url pressedIcon
    property bool checked: false
    property bool canBeChecked: true

    sourceSize.width: width
    sourceSize.height: height

    signal clicked()

    onIconChanged: {
        if(checked == true)
            source = pressedIcon
        else
            source = icon
    }

    onCheckedChanged: {
        if(checked == true)
            source = pressedIcon
        else
            source = icon
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(base.canBeChecked == true) {
                if(base.checked == true)
                    base.checked = false
                else
                    base.checked = true
                base.clicked()
            }
        }
    }
}
