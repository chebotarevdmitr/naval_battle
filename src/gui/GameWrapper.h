// src/gui/GameWrapper.h
#ifndef GAME_WRAPPER_H
#define GAME_WRAPPER_H

#include <QObject>        // Нужен для QObject и Q_OBJECT
#include "../core/Game.h" // Подключаем твою игровую логику

// Класс-обёртка, который делает C++-логику доступной в QML
class GameWrapper : public QObject
{
Q_OBJECT // ← ОБЯЗАТЕЛЬНО для сигналов и Q_INVOKABLE

    public :
    // Конструктор
    explicit GameWrapper(QObject *parent = nullptr);

    // Методы, которые можно вызывать из QML
    Q_INVOKABLE bool playerShoot(int row, int col);
    Q_INVOKABLE void resetGame();
    Q_INVOKABLE int getPlayerCell(int row, int col) const;
    Q_INVOKABLE int getEnemyCell(int row, int col) const;

signals:
    // Сигнал, который уведомляет QML: "состояние игры изменилось — перерисуй UI"
    void gameChanged();

private:
    Game game; // ← Твоя игровая логика (из Game.h/cpp)
};

#endif // GAME_WRAPPER_H