import QtQuick

Rectangle {
    required property int number

    color: number ? Qt.hsva(number * 5 / 132 + 1 / 12, 1, 1, 1) : "#00000000"
    radius: 10

    Behavior on x {
        NumberAnimation {
            duration: 100
        }
    }
    Behavior on y {
        NumberAnimation {
            duration: 100
        }
    }

    Text {
        anchors.centerIn: parent
        font.bold: true
        font.pointSize: 15
        text: number === 0 ? "" : String(1 << number)
    }
}
