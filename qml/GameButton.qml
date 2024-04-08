import QtQuick
import QtQuick.Controls

Button {
    id: root

    property color colorOne
    property color colorTwo

    background: Rectangle {
        color: root.down ? colorOne : colorTwo
        opacity: enabled ? 1 : .3
        radius: 10
    }
    contentItem: Text {
        color: "black"
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        opacity: enabled ? 1 : .3
        text: root.text
        verticalAlignment: Text.AlignVCenter
    }
}