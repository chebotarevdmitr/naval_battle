// GameView.qml
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
        color: "#b3e0ff"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 30

            Text {
                text: "Поле противника"
                font.pixelSize: 22
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
                    delegate: Rectangle {
                        id: cell
                        width: 40
                        height: 40
                        color: "#b3e0ff"
                        border.color: "#80c0ff"
                        border.width: 1

                        Rectangle {
                            id: explosion
                            anchors.centerIn: parent
                            width: 0
                            height: 0
                            color: "#ff3300"
                            radius: width / 2
                            opacity: 0
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                var row = index / 10 | 0
                                var col = index % 10
                                var isHit = game.playerShoot(row, col)

                                if (isHit) {
                                    cell.color = "#ff6666"
                                    explosion.opacity = 1
                                    explosion.width = 0
                                    explosion.height = 0
                                    explosionAnimator.start()
                                    timer.start()
                                } else {
                                    cell.color = "#cccccc"
                                }
                            }
                        }

                        Timer {
                            id: timer
                            interval: 300
                            onTriggered: cell.color = "#b3e0ff"
                        }

                        ParallelAnimation {
                            id: explosionAnimator
                            NumberAnimation {
                                target: explosion
                                property: "width"
                                to: 60
                                duration: 300
                                easing.type: Easing.OutExpo
                            }
                            NumberAnimation {
                                target: explosion
                                property: "height"
                                to: 60
                                duration: 300
                                easing.type: Easing.OutExpo
                            }
                            NumberAnimation {
                                target: explosion
                                property: "opacity"
                                to: 0
                                duration: 300
                                easing.type: Easing.OutQuad
                            }
                        }
                    }
                }
            }
        }
    }
}