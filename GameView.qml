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

    // Инициализация игры при запуске
    Component.onCompleted: game.resetGame()

    function updateCell(repeater, index, isPlayer) {
        var r = Math.floor(index / 10)
        var c = index % 10
        var val = isPlayer ? game.getPlayerCell(r, c) : game.getEnemyCell(r, c)
        var rect = repeater.itemAt(index)
        if (rect) {
            rect.color = cellColor(val, isPlayer)
            rect.childText.text = cellText(val, isPlayer)
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

                // Твоё поле — статическое отображение
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
                            model: 100
                            delegate: Rectangle {
                                width: 35
                                height: 35
                                color: {
                                    var r = index / 10 | 0
                                    var c = index % 10
                                    var val = game.getPlayerCell(r, c)
                                    cellColor(val, true)
                                }
                                Text {
                                    anchors.centerIn: parent
                                    text: {
                                        var r = index / 10 | 0
                                        var c = index % 10
                                        var val = game.getPlayerCell(r, c)
                                        cellText(val, true)
                                    }
                                    font.pixelSize: 14
                                }
                            }
                        }
                    }
                }

                // Поле противника — интерактивное
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
                            model: 100
                            delegate: Rectangle {
                                width: 35
                                height: 35
                                color: {
                                    var r = index / 10 | 0
                                    var c = index % 10
                                    var val = game.getEnemyCell(r, c)
                                    cellColor(val, false)
                                }
                                Text {
                                    anchors.centerIn: parent
                                    text: {
                                        var r = index / 10 | 0
                                        var c = index % 10
                                        var val = game.getEnemyCell(r, c)
                                        cellText(val, false)
                                    }
                                    font.pixelSize: 14
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        var r = index / 10 | 0
                                        var c = index % 10
                                        game.playerShoot(r, c)
                                        // Нет необходимости вызывать update — QML сам пересчитает color/text
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Button {
                text: "Новая игра"
                onClicked: game.resetGame()
            }
        }
    }
}
