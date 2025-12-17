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

    // Подключаемся к сигналу из C++
    Connections {
        target: game
        function onGameChanged() {
            // QML автоматически пересчитает все привязки при получении сигнала
        }
    }

    Component.onCompleted: {
        game.resetGame()
    }

    function cellColor(value, isPlayer) {
        if (isPlayer) {
            if (value === 1) return "#8B4513"; // Ship
            if (value === 3) return "#ff4d4d"; // Hit
            if (value === 2) return "#f0f0f0"; // Miss
        }
        if (value === 3) return "#ff4d4d";
        if (value === 2) return "#f0f0f0";
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
                            model: 100
                            delegate: Rectangle {
                                width: 35
                                height: 35
                                color: {
                                    var r = Math.floor(index / 10);
                                    var c = index % 10;
                                    cellColor(game.getPlayerCell(r, c), true)
                                }
                                Text {
                                    anchors.centerIn: parent
                                    text: {
                                        var r = Math.floor(index / 10);
                                        var c = index % 10;
                                        cellText(game.getPlayerCell(r, c), true)
                                    }
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
                            model: 100
                            delegate: Rectangle {
                                width: 35
                                height: 35
                                color: {
                                    var r = Math.floor(index / 10);
                                    var c = index % 10;
                                    cellColor(game.getEnemyCell(r, c), false)
                                }
                                Text {
                                    anchors.centerIn: parent
                                    text: {
                                        var r = Math.floor(index / 10);
                                        var c = index % 10;
                                        cellText(game.getEnemyCell(r, c), false)
                                    }
                                    font.pixelSize: 14
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        var r = Math.floor(index / 10);
                                        var c = index % 10;
                                        console.log("QML: выстрел по строке", r, "столбцу", c);
                                        var result = game.playerShoot(r, c);
                                        console.log("QML: результат от C++ =", result);
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
                    game.resetGame();
                }
            }
        }
    }
}