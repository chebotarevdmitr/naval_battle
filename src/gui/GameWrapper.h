// src / gui / GameWrapper.h 
#ifndef GAME_WRAPPER_H
#define GAME_WRAPPER_H

#include <QObject>
#include "../core/Game.h"

          class GameWrapper : public QObject
{
    Q_OBJECT

public:
    explicit GameWrapper(QObject *parent = nullptr);

    Q_INVOKABLE bool playerShoot(int row, int col);
    Q_INVOKABLE void resetGame();

    // Новые методы для QML
    Q_INVOKABLE int getPlayerCell(int row, int col) const;
    Q_INVOKABLE int getEnemyCell(int row, int col) const;

private:
    Game game;
};

#endif // GAME_WRAPPER_H

