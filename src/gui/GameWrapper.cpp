// src / gui / GameWrapper.cpp 
#include "GameWrapper.h"

          GameWrapper::GameWrapper(QObject * parent)
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

int GameWrapper::getPlayerCell(int row, int col) const
{
    return static_cast<int>(game.getPlayerCell(row, col));
}

int GameWrapper::getEnemyCell(int row, int col) const
{
    return static_cast<int>(game.getEnemyCell(row, col));
}
