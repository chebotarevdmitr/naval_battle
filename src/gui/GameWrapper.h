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

private:
    Game game;
};

#endif // GAME_WRAPPER_H
