import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels
import Game

ApplicationWindow {
    id: root

    function getColor(x) {
        return Qt.hsva(x * 5 / 132 + 1 / 12, 1, 1, 1);
    }
    function showNumber(x) {
        return x === 0 ? "" : String(1 << x);
    }

    minimumHeight: 520
    minimumWidth: 500
    title: "2048"
    visible: true

    ResetDialog {
        id: resetDialog
        anchors.centerIn: parent
    }

    EndDialog {
        id: endDialog
        anchors.centerIn: parent
    }

    UndoDialog {// not used
        id: undoDialog
        anchors.centerIn: parent
    }

    header: GameMenuBar {
        id: menu
        onShowScore: {
            scores.show()
        }
    }

    ColumnLayout {
        id: mainColumn
        anchors.fill: parent
        focus: true
        spacing: 25

        Keys.onPressed: event => {
            switch (event.key) {
            case Qt.Key_Down:
                // Here call GameController
                break;
            case Qt.Key_Left:
                // Here call GameController
                break;
            case Qt.Key_Right:
                // Here call GameController
                break;
            case Qt.Key_Up:
                // Here call GameController
                break;
            default:
                break;
            }
            if (!GameController.canMove() && GameController.inGame) {
                shadow.visible = true;
                GameController.inGame = false;
                endDialog.open();
            }
        }

        ColumnLayout {
            id: firstRow
            Layout.fillWidth: true
            //Layout.minimumHeight: root.height / 4
            spacing: 15

            Label {
                Layout.fillWidth: true
                text: "2048"
                horizontalAlignment: Label.AlignHCenter
                font.pointSize: 20
                background: Rectangle {
                    color: "yellow"
                    radius: 20
                }
            }
            GridLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true
                columns: 2
                rows: 2

                Label {
                    Layout.fillWidth: true
                    text: "Score: %1".arg(SaveController.score)
                    font.pointSize: 15
                }
                Label {
                    Layout.fillWidth: true
                    text: "Best score: %1".arg(SaveController.bestScore)
                }
                GameButton {
                    id: resetButton
                    Layout.fillWidth: true
                    text: "Reset"
                    colorOne: "#a81717"
                    colorTwo: "#be2121"
                }
                GameButton {
                    id: undoButton
                    Layout.fillWidth: true
                    text: "Undo"
                    colorOne: "#a87a17"
                    colorTwo: "#be9c21"
                }
            }
        }
        GridPanel {
            id: grid
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.preferredWidth: grid.height
        }
    }




}
