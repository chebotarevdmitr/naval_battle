import QtQuick
import QtQuick.Window

Window {
    width: 800
    height: 600
    visible: true
    title: "Qt Quick — работает!"

    Text {
        text: "✅ Qt Quick загружен!"
        anchors.centerIn: parent
        font.pixelSize: 24
        color: "#003366"
    }
}
