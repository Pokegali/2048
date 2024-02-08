import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import gameModule

Window {
    id: root

    function getColor(x) {
        return Qt.hsva(x * 5 / 132 + 1 / 12, 1, 1);
    }
    function showNumber(x) {
        return x === 0 ? "" : String(1 << x);
    }

    maximumHeight: minimumHeight
    maximumWidth: minimumWidth
    minimumHeight: 520
    minimumWidth: 500
    title: "2048"
    visible: true

    MenuBar {
        id: menu
        width: parent.width

        Menu {
            title: "Game"

            Action {
                text: "Best scores"
            }
            MenuSeparator {}
            Action {
                text: "Quit"
                onTriggered: Qt.quit()
            }
        }
    }
    ColumnLayout {
        id: mainColumn
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: menu.bottom
        anchors.margins: 10
        focus: true
        height: 500
        spacing: 25
        width: 500

        Keys.onPressed: event => {
            switch (event.key) {
            case Qt.Key_Down:
                GameController.move(2);
                break;
            case Qt.Key_Left:
                GameController.move(3);
                break;
            case Qt.Key_Right:
                GameController.move(1);
                break;
            case Qt.Key_Up:
                GameController.move(0);
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

        RowLayout {
            id: firstRow
            Layout.fillWidth: true
            Layout.maximumHeight: root.height / 4
            Layout.preferredHeight: 100
            spacing: 15

            Rectangle {
                Layout.fillHeight: true
                Layout.preferredWidth: parent.height
                color: "yellow"
                radius: 20

                Text {
                    anchors.centerIn: parent
                    font.pointSize: 20
                    text: "2048"
                }
            }
            GridLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true
                columns: 2
                rows: 2

                Rectangle {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Text {
                        id: scoreLabel
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Score"
                    }
                    Text {
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: scoreLabel.bottom
                        font.pointSize: 15
                        text: GameController.score.toLocaleString(Qt.locale("fr_FR"), "f", 0)
                    }
                }
                Rectangle {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Text {
                        id: bestScoreLabel
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Best score"
                    }
                    Text {
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: bestScoreLabel.bottom
                        font.pointSize: 15
                        text: SaveController.bestScore.toLocaleString(Qt.locale("fr_FR"), "f", 0)
                    }
                }
                Button {
                    id: resetButton
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumHeight: parent.height / 2
                    activeFocusOnTab: false
                    text: "Reset"

                    background: Rectangle {
                        color: resetButton.down ? "#a81717" : "#be2121"
                        opacity: enabled ? 1 : .3
                        radius: 10
                    }
                    contentItem: Text {
                        color: "black"
                        elide: Text.ElideRight
                        horizontalAlignment: Text.AlignHCenter
                        opacity: enabled ? 1 : .3
                        text: resetButton.text
                        verticalAlignment: Text.AlignVCenter
                    }

                    onClicked: resetDialog.open()
                }
                Button {
                    id: undoButton
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumHeight: parent.height / 2
                    activeFocusOnTab: false
                    text: "Undo"

                    background: Rectangle {
                        color: undoButton.down ? "#a87a17" : "#be9c21"
                        opacity: enabled ? 1 : .3
                        radius: 10
                    }
                    contentItem: Text {
                        color: "black"
                        elide: Text.ElideRight
                        horizontalAlignment: Text.AlignHCenter
                        opacity: enabled ? 1 : .3
                        text: undoButton.text
                        verticalAlignment: Text.AlignVCenter
                    }

                    onClicked: undoDialog.open()
                }
            }
        }
        Rectangle {
            id: grid
            Layout.alignment: Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.preferredWidth: grid.height
            color: "#b0b0b0"
            radius: 10

            GridLayout {
                anchors.fill: parent
                anchors.margins: 8
                columnSpacing: 8
                columns: 4
                rowSpacing: 8
                rows: 4

                Repeater {
                    model: 16

                    Rectangle {
                        required property int index

                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: GameController.board[index] ? root.getColor(GameController.board[index]) : "#a0a0a0"
                        radius: 10

                        Text {
                            anchors.centerIn: parent
                            font.bold: true
                            font.pointSize: 15
                            text: root.showNumber(GameController.board[index])
                        }
                    }
                }
            }
            Rectangle {
                id: shadow
                anchors.fill: parent
                color: "#66ffffff"
                radius: 10
                visible: false
                z: 1
            }
        }
    }
    Popup {
        id: resetDialog
        anchors.centerIn: parent
        closePolicy: Popup.CloseOnEscape
        focus: true
        modal: true
        padding: 40

        contentItem: Column {
            anchors.centerIn: parent
            spacing: 10

            Text {
                id: resetDialogText
                color: "white"
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
            shadow.visible = true;
            resetDialogText.text = GameController.canMove() ? "Your progress will be lost. Are you sure?" : "Do you want to start again?";
        }
        onClosed: {
            if (GameController.canMove()) {
                shadow.visible = false;
                mainColumn.forceActiveFocus();
            }
        }
    }
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
                    onAccepted: {
                        SaveController.registerScore(usernameInput.text, GameController.score);
                        endDialog.close();
                    }

                    validator: RegularExpressionValidator {
                        regularExpression: /.{3,30}/
                    }
                }
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Save"
                id: saveButton

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

        onAboutToShow: shadow.visible = true
        onClosed: {
            if (GameController.canMove()) {
                shadow.visible = false;
                mainColumn.forceActiveFocus();
            }
        }
    }
}