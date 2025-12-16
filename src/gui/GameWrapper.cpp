#include "GameWrapper.h"

GameWrapper::GameWrapper(QObject *parent)
    : QObject(parent)
{
    game.reset();
}

bool GameWrapper::playerShoot(int row, int col)
{
    return game.playerShoot(row, col);
}

void GameWrapper::resetGame()
{
    game.reset();
}
