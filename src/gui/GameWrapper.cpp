// src/gui/GameWrapper.cpp
#include "GameWrapper.h"
#include <QDebug> // ← для отладочного вывода (опционально, можно удалить позже)

GameWrapper::GameWrapper(QObject *parent)
    : QObject(parent)
{
    // Инициализируем игру при создании объекта
    game.reset();
}

// Обработка выстрела игрока
bool GameWrapper::playerShoot(int row, int col)
{
    // Передаём выстрел в логику игры
    bool result = game.playerShoot(row, col);

    // Выводим в терминал (для отладки)
    qDebug() << "C++: playerShoot(" << row << "," << col << ") =" << result;

    // Уведомляем QML, что состояние изменилось
    emit gameChanged();

    return result;
}

// Сброс игры
void GameWrapper::resetGame()
{
    game.reset();
    qDebug() << "C++: игра сброшена";
    emit gameChanged();
}

// Получить состояние клетки на твоём поле (0=вода, 1=корабль, 2=промах, 3=попадание)
int GameWrapper::getPlayerCell(int row, int col) const
{
    return static_cast<int>(game.getPlayerCell(row, col));
}

// Получить состояние клетки на поле противника (корабли скрыты!)
int GameWrapper::getEnemyCell(int row, int col) const
{
    return static_cast<int>(game.getEnemyCell(row, col));
}