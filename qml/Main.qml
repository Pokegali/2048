import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import gameModule

ApplicationWindow {
    id: root

    property alias gameShadow: grid.shadow

    maximumHeight: minimumHeight
    maximumWidth: minimumWidth
    minimumHeight: 520
    minimumWidth: 500
    title: "2048"
    visible: true

    header: MainMenu {
        id: menu
        onShowScores: scores.show()
        onOpenSettings: settings.open()
    }

    ColumnLayout {
        id: mainColumn
        anchors.fill: parent
        focus: true
        spacing: 10
        anchors.bottomMargin: 10

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

        GameHeader {
            Layout.margins: 15
            Layout.maximumHeight: root.height / 4
            Layout.minimumHeight: root.height / 4
        }
        GameGrid {
            id: grid
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.preferredWidth: grid.height
        }
    }

    ResetDialog {
        id: resetDialog
        anchors.centerIn: parent
    }
    EndDialog {
        id: endDialog
        anchors.centerIn: parent
    }
    UndoDialog {
        id: undoDialog
        anchors.centerIn: parent
    }
    GameSettingsDialog {
        id: settings
        anchors.centerIn: parent
    }
    ScoresWindow {
        id: scores
    }
}
