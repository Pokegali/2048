import QtQuick
import QtQuick.Controls
import QtQuick.Window
import gameModule

Popup {
    id: endDialog
    anchors.centerIn: parent
    closePolicy: Popup.CloseOnEscape
    focus: true
    modal: true
    padding: 40

    contentItem: Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
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
                color: "white"
                focus: true
                maximumLength: 30

                validator: RegularExpressionValidator {
                    regularExpression: /.{3,30}/
                }

                onAccepted: {
                    SaveController.registerScore(usernameInput.text, GameController.score);
                    endDialog.close();
                }
            }
        }
        Button {
            id: saveButton
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Save"

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
