import QtQuick
import QtQuick.Controls

MenuBar {
    id: menu
    signal openSettings
    signal showScores

    width: parent.width

    Menu {
        title: "Game"

        onAboutToHide: mainColumn.forceActiveFocus()

        Action {
            text: "Best scores"

            onTriggered: menu.showScores()
        }
        Action {
            text: "Change game settings"

            onTriggered: menu.openSettings()
        }
        MenuSeparator {
        }
        Action {
            text: "Quit"

            onTriggered: Qt.quit()
        }
    }
}
