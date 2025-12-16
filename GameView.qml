// GameView.qml 
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: window
    width: 1000
    height: 800
    visible: true
    title: "Морской бой — Qt Quick"

    // Обновляем поля при старте и после выстрела
    Component.onCompleted: updateBoards()

    function updateBoards() {
        for (var i = 0; i < 100; i++) {
            var r = Math.floor(i / 10)
            var c = i % 10

            // Обновление твоего поля
            var playerVal = game.getPlayerCell(r, c)
            var playerRect = playerRepeater.itemAt(i)
            if (playerRect) {
                playerRect.color = cellColor(playerVal, true)
                playerRect.childText.text = cellText(playerVal, true)
            }

            // Обновление поля противника
            var enemyVal = game.getEnemyCell(r, c)
            var enemyRect = enemyRepeater.itemAt(i)
            if (enemyRect) {
                enemyRect.color = cellColor(enemyVal, false)
                enemyRect.childText.text = cellText(enemyVal, false)
            }
        }
    }

    function cellColor(value, isPlayer) {
        if (isPlayer) {
            if (value === 1) return "#8B4513"; // Ship
            if (value === 3) return "#ff4d4d"; // Hit
            if (value === 2) return "#f0f0f0"; // Miss
        }
        if (value === 3) return "#ff4d4d"; // Hit
        if (value === 2) return "#f0f0f0"; // Miss
        return "#b3e0ff"; // Water
    }

    function cellText(value, isPlayer) {
        if (isPlayer) {
            if (value === 1) return "S";
            if (value === 3) return "X";
            if (value === 2) return ".";
        }
        if (value === 3) return "X";
        if (value === 2) return ".";
        return "~";
    }

    Rectangle {
        anchors.fill: parent
        color: "#e6f2ff"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20

            RowLayout {
                spacing: 50

                // Твоё поле
                ColumnLayout {
                    Text {
                        text: "Ваше поле"
                        font.pixelSize: 20
                        color: "#003366"
                    }
                    Grid {
                        rows: 10
                        columns: 10
                        rowSpacing: 1
                        columnSpacing: 1
                        Repeater {
                            id: playerRepeater
                            model: 100
                            delegate: Rectangle {
                                width: 35
                                height: 35
                                color: "#b3e0ff"
                                Text {
                                    id: childText
                                    anchors.centerIn: parent
                                    font.pixelSize: 14
                                }
                            }
                        }
                    }
                }

                // Поле противника
                ColumnLayout {
                    Text {
                        text: "Поле противника"
                        font.pixelSize: 20
                        color: "#003366"
                    }
                    Grid {
                        rows: 10
                        columns: 10
                        rowSpacing: 1
                        columnSpacing: 1
                        Repeater {
                            id: enemyRepeater
                            model: 100
                            delegate: Rectangle {
                                width: 35
                                height: 35
                                color: "#b3e0ff"
                                Text {
                                    id: childText
                                    anchors.centerIn: parent
                                    font.pixelSize: 14
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        var r = index / 10 | 0
                                        var c = index % 10
                                        var isHit = game.playerShoot(r, c)
                                        updateBoards() // обновляем сразу
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Button {
                text: "Новая игра"
                onClicked: {
                    game.resetGame()
                    updateBoards()
                }
            }
        }
    }
}