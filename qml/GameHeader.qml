import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import gameModule

Row {
    Layout.fillWidth: true
    Layout.minimumHeight: root.height / 4
    spacing: 15

    Rectangle {
        color: "yellow"
        height: parent.height
        radius: 20
        width: parent.height

        Text {
            anchors.centerIn: parent
            font.pointSize: 20
            text: "2048"
        }
    }
    GridLayout {
        columns: 2
        height: parent.height
        rows: 2
        width: parent.width - parent.height - 10

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: scoreLabel
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Score"
            }
            Text {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: scoreLabel.bottom
                font.pointSize: 15
                text: GameController.score.toLocaleString(Qt.locale("fr_FR"), "f", 0)
            }
        }
        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: bestScoreLabel
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Best score"
            }
            Text {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: bestScoreLabel.bottom
                font.pointSize: 15
                text: SaveController.bestScore.toLocaleString(Qt.locale("fr_FR"), "f", 0)
            }
        }
        Button {
            id: resetButton
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumHeight: parent.height / 2
            activeFocusOnTab: false
            text: "Reset"

            background: Rectangle {
                color: resetButton.down ? "#a81717" : "#be2121"
                opacity: enabled ? 1 : .3
                radius: 10
            }
            contentItem: Text {
                color: "black"
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignHCenter
                opacity: enabled ? 1 : .3
                text: resetButton.text
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: resetDialog.open()
        }
        Button {
            id: undoButton
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumHeight: parent.height / 2
            activeFocusOnTab: false
            text: "Undo"

            background: Rectangle {
                color: undoButton.down ? "#a87a17" : "#be9c21"
                opacity: enabled ? 1 : .3
                radius: 10
            }
            contentItem: Text {
                color: "black"
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignHCenter
                opacity: enabled ? 1 : .3
                text: undoButton.text
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: undoDialog.open()
        }
    }
}
