//src / gui / GameWrapper.cpp 
#include "GameWrapper.h"

          GameWrapper::GameWrapper(QObject * parent)
    : QObject(parent)
{
    game.reset();
}

bool GameWrapper::playerShoot(int row, int col)
{
    bool result = game.playerShoot(row, col);
    emit gameChanged(); // ← уведомляем QML
    return result;
}

void GameWrapper::resetGame()
{
    game.reset();
    emit gameChanged();
}

int GameWrapper::getPlayerCell(int row, int col) const
{
    return static_cast<int>(game.getPlayerCell(row, col));
}

int GameWrapper::getEnemyCell(int row, int col) const
{
    return static_cast<int>(game.getEnemyCell(row, col));
}
