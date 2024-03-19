import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels
import Game

ApplicationWindow {
    id: root

    property alias gameShadow: grid.shadow

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
                GameController.move(GameController.Direction.down);
                break;
            case Qt.Key_Left:
                GameController.move(GameController.Direction.left);
                break;
            case Qt.Key_Right:
                GameController.move(GameController.Direction.right);
                break;
            case Qt.Key_Up:
                GameController.move(GameController.Direction.up);
                break;
            default:
                break;
            }
            if (!GameController.canMove() && GameController.inGame) {
                gameShadow.visible = true;
                GameController.inGame = false;
                endDialog.open();
            }
        }

        GameHeader {}

        GameGrid {
            id: grid
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.preferredWidth: grid.height
        }
    }
}
