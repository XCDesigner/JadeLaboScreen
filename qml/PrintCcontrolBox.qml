import QtQuick 2.0

Rectangle {
  id: base
  width: 640
  height: 240
  color: "#2d2c2a"
  radius: 20

  property bool settingEnabled: true
  property bool stopEnabled: true
  property bool pauseEnabled: true

  signal settingClicked()
  signal stopClicked()
  signal pauseClicked()

  onOptionEnabledChanged: {
    if(optionEnabled == true) source: "qrc:/image/setting.png"
    else source: "qrc:/image/setting_disabled.png"
  }

  onStopEnabled: {
    if(optionEnabled == true) source: "qrc:/image/Stop.png"
    else source: "qrc:/image/Stop_disabled.png"
  }

  onPauseEnabled: {
    if(optionEnabled == true) source: "qrc:/image/pause.png"
    else source: "qrc:/image/pause_disabled.png"
  }

  Image {
    x: 42
    y: 50
    width: 140
    height: 130
    sourceSize.height: height
    sourceSize.width: width
    source: "qrc:/image/setting.png"
    MouseArea {
      anchors.fill: parent
      onClicked:  {
        if(base.optionEnabled == true) base.settingClicked()
      }
    }
  }

  Image {
    x: 272
    y: 55
    width: 120
    height: 120
    sourceSize.height: height
    sourceSize.width: width
    source: "qrc:/image/Stop.png"
    MouseArea {
      anchors.fill: parentonClicked:  {
        if(base.stopEnabled == true) base.stopClicked()
      }
    }
  }

  Image {
    x: 472
    y: 55
    width: 120
    height: 120
    sourceSize.height: height
    sourceSize.width: width
    source: "qrc:/image/pause.png"
    MouseArea {
      anchors.fill: parent
      onClicked:  {
        if(base.pauseEnabled == true) base.pauseClicked()
      }
    }
  }
}
