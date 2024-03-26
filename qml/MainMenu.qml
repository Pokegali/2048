import QtQuick.Controls

MenuBar {
    Menu {
        title: "Game"

        onAboutToHide: mainColumn.forceActiveFocus()

        Action {
            text: "Best scores"

            onTriggered: scores.show()
        }
        Action {
            text: "Change game settings"

            onTriggered: settings.open()
        }
        MenuSeparator {
        }
        Action {
            text: "Quit"

            onTriggered: Qt.quit()
        }
    }
}
