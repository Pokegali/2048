import QtQuick
import QtQuick.Layouts
import gameModule

Window {
    id: root

    property alias gameShadow: grid.shadow

    maximumHeight: minimumHeight
    maximumWidth: minimumWidth
    minimumHeight: 520
    minimumWidth: 500
    title: "2048"
    visible: true

    MainMenu {
        id: menu
        width: parent.width
    }
    ColumnLayout {
        id: mainColumn
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 10
        anchors.right: parent.right
        anchors.top: menu.bottom
        focus: true
        height: 500
        spacing: 25
        width: 500

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
        }
    }
    ResetDialog {
        id: resetDialog
    }
    EndDialog {
        id: endDialog
    }
    UndoDialog {
        id: undoDialog
    }
    GameSettingsDialog {
        id: settings
    }
    ScoresWindow {
        id: scores
    }
}
