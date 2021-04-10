import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0


Rectangle {
  id: base

  anchors.fill: parent
  height: 56
  width: 384
//  color: "transparent"

  property int itemSelect
  property int distance: 1000

  Rectangle {
    id: item1
    x: 0
    y: 0
    width: 104
    height: 56
    radius: 8
    color: "#474747"

    Text {
      anchors.centerIn: parent
      color: "white"
      text: "0.1"
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
      anchors.fill: parent
      onReleased: {
        base.changeSelect(1)
      }
    }
  }

  Rectangle {
    id: item4
    x: 279
    y: 0
    width: 104
    height: 56
    radius: 8
    color: "#474747"

    Text {
      anchors.centerIn: parent
      color: "white"
      text: "100"
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
      anchors.fill: parent
      onReleased: {
        base.changeSelect(4)
      }
    }
  }

  Rectangle {
    id: item2
    x: 95
    y: 0
    width: 96
    height: 56
    color: "#F17535"

    Text {
      anchors.centerIn: parent
      color: "white"
      text: "1"
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
      anchors.fill: parent
      onReleased: {
        base.changeSelect(2)
      }
    }
  }

  Rectangle {
    id: item3
    x: 191
    y: 0
    width: 96
    height: 56
    color: "#474747"

    Text {
      anchors.centerIn: parent
      color: "white"
      text: "10"
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
      anchors.fill: parent
      onReleased: {
        base.changeSelect(3)
      }
    }
  }

  function changeSelect(Item) {
    item1.color = "#474747"
    item2.color = "#474747"
    item3.color = "#474747"
    item4.color = "#474747"
    if(Item === 1) {
      item1.color = "#F17535"
      itemSelect = Item
      distance = 100
    }
    else if(Item === 2) {
      item2.color = "#F17535"
      itemSelect = Item
      distance = 1000
    }
    else if(Item === 3) {
      item3.color = "#F17535"
      itemSelect = Item
      distance = 10000
    }
    else if(Item === 4) {
      item4.color = "#F17535"
      itemSelect = Item
      distance = 100000
    }
  }

}
