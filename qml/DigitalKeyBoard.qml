import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: base
    radius: 20

    width: 428
    height: 572

    color: "#2d2c2b"

    property int keyBorderWidth: 4
    property color keyBorderColor: "#f0f0f0"

    signal keyEnter(string value)

    GridLayout {
        anchors.centerIn: parent
        rows: 4
        columns: 3
        rowSpacing: 4
        columnSpacing: 4
        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 0
            Layout.row: 0
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "7"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("7")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 1
            Layout.row: 0
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "8"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("8")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 2
            Layout.row: 0
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "9"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("9")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 0
            Layout.row: 1
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "4"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("4")
                }
            }
        }

        Rectangle {color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 1
            Layout.row: 1
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "5"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("5")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 2
            Layout.row: 1
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "6"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("6")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 0
            Layout.row: 2
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "1"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("1")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 1
            Layout.row: 2
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "2"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("2")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 2
            Layout.row: 2
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "3"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("3")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 0
            Layout.row: 3
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "."
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter(".")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 1
            Layout.row: 3
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "0"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("0")
                }
            }
        }

        Rectangle {
            color: "#ff630b"
            width: 140
            height: 140
            Layout.column: 2
            Layout.row: 3
            radius: 10
            border.color: base.keyBorderColor
            border.width: base.keyBorderWidth
            Text {
                anchors.centerIn: parent
                text: "<-"
                color: "#f0f0f0"
                font { family: "barlow"; pixelSize: 48; bold: true}
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    base.keyEnter("bk")
                }
            }
        }

    }

}
