import QtQuick 2.12
import QtQuick.Controls 2.0

Rectangle {
    id: base

    width: 247
    height: 72
    color: "#ff630b"

    ComboBox {
        id: cmbSelect
        x:0
        y:0
        width: 247
        height: 288
        model: ["0.1","0.01","0.2"]
        background: Rectangle {
            radius: 10
            color: "#ff630b"
        }
        delegate: ItemDelegate {
            width: parent.width
            height: 72
            contentItem: Text {
                height: 72
                width: parent.width
                text: modelData + "mm"
                color: "#ffffff"
                font { family: "barlow"; pixelSize: 36; bold:true}
            }
        }

        contentItem: Text {

            text: cmbSelect.displayText
            font: cmbSelect.font
            color: cmbSelect.pressed ? "#17a81a" : "#21be2b"
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        onAccepted: {
            txtValue.text = cmbSelect.currentText;
        }
    }
}
