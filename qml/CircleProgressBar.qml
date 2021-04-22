import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.0

import QtQuick.Controls.Styles 1.4

Rectangle{
  id: base

  property alias currentPercent: canvas.percent
  property alias text: label_text.text
  property bool finishEnabled: false

  color: "transparent"

  signal receFromWidget(int printRec)
  signal finishClicked()

  function setPercent(printRec)
  {
    canvas.percent = printRec;
    lable_percent.text = printRec + "%";
  }
  Component.onCompleted:
  {
      base.receFromWidget.connect(base.setPercent);
  }
  Component.onDestruction:
  {
      base.receFromWidget.disconnect(base.setPercent);
  }

  onCurrentPercentChanged: {
    canvas.requestPaint()
      lable_percent.text = currentPercent + "%"
  }

  onFinishEnabledChanged: {
      if(finishEnabled == true) {
          lable_percent.text = "Finish"
          tmr.running = true
      }
      else {
          lable_percent.text = currentPercent + "%"
          tmr.running = false
      }
  }

  Timer {
    id: tmr
    interval: 100
    repeat: true
    running: false
    property bool inc: true
    onTriggered: {
      if(inc == true) {
        if(canvas.stop0 < 0.65)
          canvas.stop0 = canvas.stop0 + 0.02
        else
          inc = false
      }
      else {
        if(canvas.stop0 > 0.45)
          canvas.stop0 = canvas.stop0 - 0.02
        else
          inc = true
      }
      canvas.requestPaint()
    }
  }

  Canvas {
    id: canvas

    property int percent
    property real stop0: 0.5

    anchors.fill: parent

    onPaint : {
      var ctx = canvas.getContext('2d');
      ctx.clearRect(0, 0, parent.width, parent.height);
      var gradient

      if(base.finishEnabled == false) {
          ctx.beginPath();
          ctx.lineWidth = 2;
          ctx.fillStyle = "#000000";
          ctx.ellipse(0, 0, parent.width, parent.height);
          ctx.closePath();
          ctx.fill();

          ctx.beginPath();
          ctx.lineWidth = 2;
          ctx.fillStyle = "#202020";
          ctx.ellipse(58, 58, parent.width-116, parent.height-116);
          ctx.closePath();
          ctx.fill();

          ctx.beginPath();
          ctx.lineCap = "round"
          ctx.lineWidth = 58;
          gradient = ctx.createConicalGradient(parent.width / 2, parent.height / 2, Math.PI/2)
          // gradient.addColorStop(, "#F3B67B")
          gradient.addColorStop(0, "#F3B67B")
          gradient.addColorStop(0.5, "#FF5B00")
          gradient.addColorStop(0.75, "#F3B67B")
          ctx.strokeStyle = gradient
          ctx.arc(parent.width / 2, parent.height / 2, parent.width / 2 - 29, -Math.PI / 2, -Math.PI / 2 + percent / 100* (Math.PI * 2), false);
          ctx.stroke();
          ctx.closePath();
      }
      else {
          gradient = ctx.createRadialGradient(parent.width / 2, parent.height / 2 , parent.width/2 * 0.6, parent.width / 2, parent.height / 2, parent.width / 2)
          gradient.addColorStop(0, "#202020")
          gradient.addColorStop(0.2, "#202020")
          gradient.addColorStop(0.41, "#00ff00")
          gradient.addColorStop(stop0, "#00ff00")
          gradient.addColorStop(1, "#202020")

          ctx.lineWidth = 0.1;
          ctx.strokeStyle = "#202020"
          ctx.beginPath();
          ctx.ellipse(0, 0, parent.width, parent.height)
          // ctx.stroke();
          ctx.closePath();
          ctx.fillStyle = gradient
          ctx.fill()
      }
    }
  }

  Label {
    id: lable_percent

    anchors.centerIn: parent
    font {pixelSize: 64; bold: true}
    color: "white"
    text: currentPercent + "%"
  }

  MouseArea {
      anchors.centerIn: parent
      width: 300
      height: 300
      onClicked: {
          if(base.finishEnabled == true) {
              base.finishClicked()
          }
      }
  }

  Label {
    id: label_text
    anchors {top: lable_percent.bottom; horizontalCenter:parent.horizontalCenter; margins: 10}
    color: "white"
    font {
            pixelSize: 64;
            family: "Barlow";
    }
  }

}
