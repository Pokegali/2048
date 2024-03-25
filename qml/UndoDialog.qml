import QtQuick
import QtQuick.Controls
import gameModule

Popup {
    id: undoDialog
    anchors.centerIn: parent
    closePolicy: Popup.CloseOnEscape
    focus: true
    modal: true
    padding: 40

    contentItem: Column {
        spacing: 10

        Text {
            color: "white"
            text: "No, you can't cheat! It's bad."
        }
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Ok"

            onClicked: undoDialog.close()
        }
    }

    onAboutToShow: gameShadow.visible = true
    onClosed: {
        if (GameController.canMove()) {
            gameShadow.visible = false;
            mainColumn.forceActiveFocus();
        }
    }
}
