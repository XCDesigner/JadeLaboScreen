import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: base
    color: "transparent"

    Timer{
        interval: 200
        repeat: true
        running: true
        property bool inc: true
        onTriggered: {
            if(inc == true) {
                if(canvas.stop0 < 0.78)
                    canvas.stop0 = canvas.stop0 + 0.02
                else
                    inc = false
            }
            else {
                if(canvas.stop0 > 0.46)
                    canvas.stop0 = canvas.stop0 - 0.02
                else
                    inc = true
            }

            canvas.requestPaint()
        }
    }

    Canvas {
        id: canvas
        property real stop0: 0.5
        property real thickness: base.width / 2 * 0.9

        anchors.fill: parent

        onPaint : {
            var ctx = canvas.getContext('2d');
            ctx.clearRect(0, 0, parent.width, parent.height);

            // ctx.lineCap = "round"

            var gradient = ctx.createRadialGradient(parent.width / 2, parent.height / 2 , thickness, parent.width / 2, parent.height / 2, parent.width / 2)
            gradient.addColorStop(0, "#202020")
            gradient.addColorStop(0.5, "#202020")
            gradient.addColorStop(0.44, "#ff0000")
            gradient.addColorStop(stop0, "#202020")
            gradient.addColorStop(1, "#202020")

            ctx.lineWidth = 0.1;
            ctx.strokeStyle = "#202020"
            ctx.beginPath();
            ctx.ellipse(0, 0, parent.width, parent.height)
            ctx.closePath();
            ctx.fillStyle = gradient
            ctx.fill()
        }
    }

    Label {
      id: lable_heating

      anchors.centerIn: parent
      font {
          pixelSize: 64;
          family: "Barlow";
          bold: true
      }
      color: "white"
      text: "Heating"
    }

}
