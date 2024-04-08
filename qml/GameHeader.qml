import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import gameModule

GridLayout {
    columns: 3
    columnSpacing: 10
    rowSpacing: 5

    Label {
        Layout.fillHeight: true
        Layout.preferredWidth: height
        Layout.rowSpan: 2
        font.pointSize: 20
        text: "2048"
        color: "black"
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter

        background: Rectangle {
            color: "yellow"
            radius: 20
        }
    }
    Label {
        Layout.preferredWidth: 500
        Layout.fillHeight: true
        Layout.fillWidth: true
        font.pointSize: 14
        horizontalAlignment: Label.AlignHCenter
        text: "Score<br/><strong>%1</strong>".arg(GameController.score.toLocaleString(Qt.locale("fr_FR"), "f", 0))
        textFormat: Label.RichText
    }
    Label {
        Layout.preferredWidth: 500
        Layout.fillHeight: true
        Layout.fillWidth: true
        font.pointSize: 14
        horizontalAlignment: Label.AlignHCenter
        text: "Best score %1<br/><strong>%2</strong>".arg(GameController.gameSize === 4 ? "" : "4×4").arg(SaveController.bestScore.toLocaleString(Qt.locale("fr_FR"), "f", 0))
        textFormat: Label.RichText
    }
    GameButton {
        id: resetButton
        Layout.fillHeight: true
        Layout.fillWidth: true
        colorOne: "#a81717"
        colorTwo: "#be2121"
        text: "Reset"
        onClicked: resetDialog.open()
    }
    GameButton {
        id: undoButton
        Layout.fillHeight: true
        Layout.fillWidth: true
        colorOne: "#a87a17"
        colorTwo: "#be9c21"
        text: "Undo"
        onClicked: undoDialog.open()
    }
}