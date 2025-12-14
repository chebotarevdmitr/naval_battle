// qml/GameView.qml
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: window
    width: 900
    height: 700
    visible: true
    title: "Морской бой — Qt Quick"

    Rectangle {
        anchors.fill: parent
        color: "#b3e0ff" // морской фон

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 30

            Text {
                text: "Ваше поле"
                font.pixelSize: 20
                color: "#003366"
                Layout.alignment: Qt.AlignHCenter
            }

            Grid {
                id: playerGrid
                rows: 10
                columns: 10
                rowSpacing: 2
                columnSpacing: 2

                Repeater {
                    model: 100
                    Rectangle {
                        width: 40
                        height: 40
                        color: "#8B4513"  // коричневый — корабль (временно)
                        border.color: "#5a2f0f"
                        border.width: 1

                        Text {
                            text: "S"
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            anchors.fill: parent
                        }
                    }
                }
            }

            Text {
                text: "Поле противника"
                font.pixelSize: 20
                color: "#003366"
                Layout.alignment: Qt.AlignHCenter
            }

            Grid {
                id: enemyGrid
                rows: 10
                columns: 10
                rowSpacing: 2
                columnSpacing: 2

                Repeater {
                    model: 100
                    Rectangle {
                        width: 40
                        height: 40
                        color: "#b3e0ff" // вода
                        border.color: "#80c0ff"
                        border.width: 1

                        Text {
                            text: "~"
                            color: "#2c5aa0"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            anchors.fill: parent
                        }
                    }
                }
            }
        }
    }
}