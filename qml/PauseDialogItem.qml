import QtQuick 2.0
import QtQuick.Layouts 1.2

Rectangle {
    id: base
    width: 1280
    height: 720
    color: "transparent"

    property bool leftEnable: leftExtruderEnable.isPressed
    property bool rightEnable: rightExtruderEnable.isPressed
    property bool nonAvoidEnable: true
    property string curStatus: "running"

    signal pauseClicked()
    signal continueClicked()
    signal changeFilamentClicked()
    signal cancelClicked()

    onLeftEnableChanged: {
        leftExtruderEnable.isPressed = leftEnable
    }

    onRightEnableChanged: {
        rightExtruderEnable.isPressed = rightEnable
    }

    onNonAvoidEnableChanged: {
        if(nonAvoidEnable == true){
            leftExtruderEnable.visible = true
            rightExtruderEnable.visible = true
        }
        else {
            leftExtruderEnable.visible = false
            rightExtruderEnable.visible = false
        }
    }

    onCurStatusChanged: {
        if(curStatus == "running") {
            btnPauseContinue.text = "Pause"
        }
        else if(curStatus == "pause")
        {
            btnPauseContinue.text = "Continue"
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        JLPushedButton {
            id: btnPauseContinue
            text: "Pause"
            isPressed: true
            width: 1008
            height: 120
            onClicked: {
                if(text == "Pause")
                    base.pauseClicked()
                else if(text == "Continue")
                    base.continueClicked()
            }
        }

        JLPushedButton {
            id: btnChangeFilament
            text: "Change Filament"
            isPressed: true
            width: 1008
            height: 120
            onClicked: base.changeFilamentClicked()
        }

        RowLayout {
            spacing: 20
            JLPushedButton {
                id: leftExtruderEnable
                width: 494
                height: 120
                isPressed: true
                text: "Left Extruder Enable"
                onClicked: {
                    if(leftExtruderEnable.isPressed == true)
                    {
                        if(rightExtruderEnable.isPressed == true)
                            leftExtruderEnable.isPressed = false;
                    }
                    else
                    {
                        leftExtruderEnable.isPressed = true
                    }
                }
            }
            JLPushedButton {
                id: rightExtruderEnable
                width: 494
                height: 120
                isPressed: true
                text: "Right Extruder Enable"
                onClicked: {
                    if(rightExtruderEnable.isPressed == true)
                    {
                        if(leftExtruderEnable.isPressed == true)
                            rightExtruderEnable.isPressed = false;
                    }
                    else
                    {
                        rightExtruderEnable.isPressed = true
                    }
                }
            }
        }

        JLPushedButton {
            id: btnCancel
            text: "Cancel"
            isPressed: true
            width: 1008
            height: 120
            onClicked: base.cancelClicked()
        }
    }
}
