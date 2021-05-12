import QtQuick 2.9

Rectangle {
    id: base

    property alias source: player.source
    property alias playing: player.playing

    AnimatedImage {
        id: player

        anchors.fill: parent
        playing: true
    }
}
