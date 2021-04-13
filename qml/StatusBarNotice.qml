import QtQuick 2.0

Rectangle {
    id: base

    width: 118
    height: 43
    color: "transparent"

    property bool udiskVisible: true
    property bool lightVisible: true
    property bool wifiVisible: true

    property alias udiskIcon: icbUdisk.icon
    property alias udiskPressedIcon: icbUdisk.pressedIcon
    property alias lightIcon: icbLight.icon
    property alias lightPressedIcon: icbLight.pressedIcon
    property alias wifiIcon: icbWifi.icon
    property alias wifiPressedIcon: icbWifi.pressedIcon

    signal udiskClicked()
    signal lightChecked()
    signal wifiClicked()

    onUdiskVisibleChanged: {
        if(udiskVisible == true)
            icbUdisk.width = 0
        else
            icbUdisk.width = 40
    }

    onLightVisibleChanged: {
        if(lightVisible == true)
            icbLight.width = 0
        else
            icbLight.width = 30
    }

    onWifiVisibleChanged: {
        if(wifiVisible == true)
            icbWifi.width = 0
        else
            icbWifi.width = 48
    }

    IconCheckedButton {
        id: icbUdisk
        width: 40
        height: 42
        checked: true
        canBeChecked: false
        anchors { right: base.right; margins: 10}
        icon: "qrc:/image/Udisk.png"
        pressedIcon: "qrc:/image/Udisk.png"
        onClicked: base.udiskClicked()
    }

    IconCheckedButton {
        id: icbLight
        width: 30
        height: 43
        checked: true
        anchors { right: icbUdisk.left; margins: 10}
        icon: "qrc:/image/Light.png"
        pressedIcon: "qrc:/image/Light.png"
        onClicked: base.lightClicked()
    }

    IconCheckedButton {
        id: icbWifi
        width: 48
        height: 42
        checked: true
        canBeChecked: false
        anchors { right: icbLight.left; margins: 10}
        icon: "qrc:/image/Wifi.png"
        pressedIcon: "qrc:/image/Wifi.png"
        onClicked: base.wifiClicked()
    }
}
