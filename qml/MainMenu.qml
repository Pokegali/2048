import QtQuick.Controls

MenuBar {
    Menu {
        title: "Game"

        onClosed: mainColumn.forceActiveFocus()

        Action {
            text: "Best scores"

            onTriggered: scores.show()
        }
        Action {
            text: "Change board size"

            onTriggered: console.log("change game size")
        }
        MenuSeparator {
        }
        Action {
            text: "Quit"

            onTriggered: Qt.quit()
        }
    }
}
