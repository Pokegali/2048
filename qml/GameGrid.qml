import QtQuick
import QtQuick.Layouts
import gameModule

Rectangle {
    id: grid
    property alias shadow: shadow
    property int spacing: 32 / GameController.gameSize

    color: "#b0b0b0"
    radius: 10

    Repeater {
        model: GameController.board

        Tile {
            required property int index
            required property bool toDelete
            required property int value

            height: gridSpaces.itemAt(index).height
            number: value
            width: gridSpaces.itemAt(index).width
            x: gridSpaces.itemAt(index).x + spacing
            y: gridSpaces.itemAt(index).y + spacing
            z: 1

            NumberAnimation on opacity  {
                id: fadeInAnimation
                duration: 100
                from: 0
                to: 1
            }
            NumberAnimation on opacity  {
                id: fadeOutAnimation
                duration: 100
                from: 1
                running: toDelete
                to: 0

                onFinished: GameController.deleteTileAt(index)
            }
        }
    }
    GridLayout {
        anchors.fill: parent
        anchors.margins: spacing
        columnSpacing: spacing
        columns: GameController.gameSize
        rowSpacing: spacing
        rows: GameController.gameSize

        Repeater {
            id: gridSpaces
            model: GameController.gameSize ** 2

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "#a0a0a0"
                radius: 10
            }
        }
    }
    Rectangle {
        id: shadow
        anchors.fill: parent
        color: "#66ffffff"
        radius: 10
        visible: false
        z: 1
    }
}
