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

  onSettingEnabledChanged: {
    if(settingEnabled == true) btnSetting.source = "qrc:/image/setting.png"
    else btnSetting.source = "qrc:/image/setting_disabled.png"
  }

  onStopEnabledChanged: {
    if(stopEnabled == true) btnStop.source = "qrc:/image/Stop.png"
    else btnStop.source = "qrc:/image/Stop_disabled.png"
  }

  onPauseEnabledChanged: {
    if(pauseEnabled == true) btnPause.source = "qrc:/image/pause.png"
    else btnPause.source = "qrc:/image/pause_disabled.png"
  }

  Image {
    id: btnSetting
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
        if(base.settingEnabled == true) base.settingClicked()
      }
    }
  }

  Image {
    id: btnStop
    x: 272
    y: 55
    width: 120
    height: 120
    sourceSize.height: height
    sourceSize.width: width
    source: "qrc:/image/Stop.png"
    MouseArea {
      anchors.fill: parent
      onClicked:  {
        if(base.stopEnabled == true) base.stopClicked()
      }
    }
  }

  Image {
    id: btnPause
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
