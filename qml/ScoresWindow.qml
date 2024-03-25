import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels
import gameModule

Window {
    id: scores
    maximumHeight: minimumHeight
    maximumWidth: minimumWidth
    minimumHeight: 450
    minimumWidth: 360
    title: "2048 | Best scores"

    TableView {
        anchors.fill: parent
        anchors.margins: 20
        clip: true
        columnSpacing: 1
        contentItem.anchors.horizontalCenter: horizontalCenter
        interactive: false
        rowSpacing: 1

        ScrollBar.vertical: ScrollBar {
            active: true
        }
        delegate: Rectangle {
            border.width: 1
            implicitHeight: 30
            implicitWidth: 100

            Text {
                anchors.centerIn: parent
                text: display
            }
        }
        model: TableModel {
            rows: SaveController.scores.map(x => ({
                            "score": x.score.toLocaleString(Qt.locale("fr_FR"), "f", 0),
                            "username": x.username,
                            "date": x.date.toLocaleDateString("fr-FR")
                        }))

            TableModelColumn {
                display: "score"
            }
            TableModelColumn {
                display: "username"
            }
            TableModelColumn {
                display: "date"
            }
        }
    }
}
