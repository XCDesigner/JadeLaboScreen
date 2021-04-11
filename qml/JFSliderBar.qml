import QtQuick 2.0

Rectangle {
    id: base
    color: "transparent"
    width: 1000
    height: 100

    property int value: 0
    property bool isPressed: false

    signal pressed()
    signal released()

    Rectangle {
        id: backgrouund
        radius: 15
        height: backgrouund.radius * 2
        x: (base.height / 2) - backgrouund.radius
        y: (base.height / 2) - backgrouund.radius
        width: base.width - backgrouund.x * 2
        color: "#808080"
    }

    Rectangle {
        id: slider

        property int bigRadius: base.height / 2
        property int smallRadius: 25

        x: bigRadius - smallRadius
        y: base.height / 2 - smallRadius
        width: smallRadius * 2
        height: smallRadius * 2
        radius: smallRadius
        color: "#FF630B"
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            slider.height = slider.bigRadius * 2
            slider.width = slider.bigRadius * 2
            slider.radius = slider.bigRadius
            slider.x = slider.x - (slider.bigRadius - slider.smallRadius)
            slider.y = 0
            base.isPressed = true
            base.pressed()

            if(mouseX < slider.bigRadius)
                slider.x = 0
            else if(mouseX > base.width - slider.bigRadius)
                slider.x = base.width - slider.bigRadius - slider.bigRadius
            else
                slider.x = mouseX - slider.width / 2
            base.value = slider.x * 100 / (base.width - slider.bigRadius - slider.bigRadius)
            //console.log(base.value)
        }
        onReleased: {
            slider.height = slider.smallRadius * 2
            slider.width = slider.smallRadius * 2
            slider.radius = slider.smallRadius
            slider.x = slider.x + (slider.bigRadius - slider.smallRadius)
            slider.y = (slider.bigRadius - slider.smallRadius)
            base.isPressed = false
            base.released()
            base.value = slider.x * 100 / (base.width - slider.bigRadius - slider.bigRadius)
            //console.log(base.value)
        }
        onPositionChanged: {
            if(mouseX < 60)
                slider.x = 0
            else if(mouseX > base.width - slider.bigRadius)
                slider.x = base.width - slider.bigRadius - slider.bigRadius
            else
                slider.x = mouseX - slider.width / 2
            base.value = slider.x * 100 / (base.width - slider.bigRadius - slider.bigRadius)
        }
    }

}
