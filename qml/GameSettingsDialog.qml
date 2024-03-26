import QtQuick
import QtQuick.Controls
import gameModule

Popup {
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
            color: root.palette.text
            text: "Game settings"
        }
        Grid {
            columns: 2
            anchors.horizontalCenter: parent.horizontalCenter
            columnSpacing: 15

            Text {
                color: root.palette.text
                text: "Game size (default 4)"
            }
            Row {
                spacing: 6

                RoundButton {
                    text: "-"
                    onClicked: {
                        GameController.gameSize--;
                        GameController.inGame = true;
                    }
                    enabled: GameController.gameSize > 2
                    height: gameSizeText.height
                    width: gameSizeText.height + 5
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 5
                }
                Text {
                    id: gameSizeText
                    color: root.palette.text
                    text: GameController.gameSize
                }
                RoundButton {
                    text: "+"
                    onClicked: {
                        GameController.gameSize++;
                        GameController.inGame = true;
                    }
                    enabled: GameController.gameSize < 8
                    height: gameSizeText.height
                    width: gameSizeText.height + 5
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 5
                }
            }
        }
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Ok"
            onClicked: settings.close()
        }
    }

    onAboutToShow: {
        gameShadow.visible = true;
    }
    onClosed: {
        if (GameController.canMove()) {
            gameShadow.visible = false;
            mainColumn.forceActiveFocus();
        }
    }
}
