import QtQuick
import QtQuick.Controls
import gameModule

Popup {
    closePolicy: Popup.CloseOnEscape
    focus: true
    modal: true
    padding: 40

    contentItem: Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            id: resetDialogText
            color: root.palette.text
        }
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Button {
                text: "No"

                onClicked: resetDialog.close()
            }
            Button {
                text: "Yes"

                onClicked: {
                    GameController.reset();
                    GameController.inGame = true;
                    resetDialog.close();
                }
            }
        }
    }

    onAboutToShow: {
        gameShadow.visible = true;
        resetDialogText.text = GameController.canMove() ? "Your progress will be lost. Are you sure?" : "Do you want to start again?";
    }
    onClosed: {
        if (GameController.canMove()) {
            gameShadow.visible = false;
            mainColumn.forceActiveFocus();
        }
    }
}
