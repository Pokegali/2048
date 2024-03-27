import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import gameModule

GridLayout {
    id: firstRow
    columns: 3
    Label {
        Layout.fillHeight: true
        text: "2048"
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter
        Layout.preferredWidth: height
        font.pointSize: 20
        Layout.rowSpan: 2
        background: Rectangle {
            color: "yellow"
            radius: 20
        }
    }
    Label {
        Layout.minimumWidth: resetButton.width
        text: "Score<br/><strong>%1</strong>".arg(1)//SaveController.score
        textFormat: Label.RichText
        horizontalAlignment: Label.AlignHCenter
        font.pointSize: 15
    }
    Label {
        Layout.minimumWidth: resetButton.width
        text: "Best score<br/><strong>%1</strong>".arg(SaveController.bestScore)
        textFormat: Label.RichText
        horizontalAlignment: Label.AlignHCenter
        font.pointSize: 15
    }
    GameButton {
        id: resetButton
        Layout.fillWidth: true
        Layout.fillHeight: true
        implicitWidth: 0
        text: "Reset"
        colorOne: "#a81717"
        colorTwo: "#be2121"
    }
    GameButton {
        id: undoButton
        Layout.fillWidth: true
        Layout.fillHeight: true
        implicitWidth: 0
        text: "Undo"
        colorOne: "#a87a17"
        colorTwo: "#be9c21"
    }
}
