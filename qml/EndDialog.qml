import QtQuick
import QtQuick.Controls
import QtQuick.Window
import gameModule

Popup {
    id: endDialog

    closePolicy: Popup.CloseOnEscape
    focus: true
    modal: true
    padding: 40

    contentItem: Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: root.palette.text
            horizontalAlignment: Text.AlignHCenter
            text: `End of game! Your score is ${GameController.score.toLocaleString(Qt.locale("fr_FR"), "f", 0)}.\nEnter a username if you wish to save your score.`
        }
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#00000000"
            height: 40
            width: usernameInput.implicitWidth + 1

            TextInput {
                id: usernameInput
                activeFocusOnTab: true
                anchors.centerIn: parent
                autoScroll: false
                color: root.palette.text
                focus: true
                maximumLength: 30
                enabled: GameController.gameSize == 4

                validator: RegularExpressionValidator {
                    regularExpression: /.{3,30}/
                }

                onAccepted: {
                    SaveController.registerScore(usernameInput.text, GameController.score);
                    endDialog.close();
                }
            }
        }
        Text {
            color: "red"
            text: "Sorry, you can only save your score in 4×4"
            visible: GameController.gameSize != 4
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Button {
            id: saveButton
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Save"
            enabled: GameController.gameSize == 4

            onClicked: {
                if (!usernameInput.acceptableInput) {
                    return;
                }
                SaveController.registerScore(usernameInput.text, GameController.score);
                endDialog.close();
            }
        }
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Don't save"

            onClicked: endDialog.close()
        }
    }
}
