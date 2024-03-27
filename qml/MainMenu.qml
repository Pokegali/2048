import QtQuick
import QtQuick.Controls

MenuBar {
    id: menu
    width: parent.width

    signal showScore();
    signal openSettings();
    Menu {
        title: "Game"
        onAboutToHide: mainColumn.forceActiveFocus()

        Action {
            text: "Best scores"

            onTriggered: menu.showScore()
        }
        Action {
            text: "Change game settings"

            onTriggered: menu.openSettings()
        }
        MenuSeparator {}
        Action {
            text: "Quit"
            onTriggered: Qt.quit()
        }
    }
}
