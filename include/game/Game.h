// include/game/Game.h
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <queue>
#include <random>

const int BOARD_SIZE = 10;

// Просто для совместимости — больше не используется для логики победы
struct Ship
{
  int dummy; // можно даже удалить, но оставим для будущего
};

class BotState
{
public:
  std::queue<std::pair<int, int>> targetQueue;
  std::vector<std::vector<bool>> shot;

  BotState();
  bool hasShot(int row, int col) const;
  void markShot(int row, int col);
  void addTargetNeighbors(int hitRow, int hitCol);
};

class Game
{
public:
  enum Cell
  {
    Water = 0,
    ShipPart,
    Miss,
    Hit
  };

  Game();
  void reset();
  bool playerShoot(int row, int col);
  void botTurn();
  Cell getPlayerCell(int row, int col) const;
  Cell getEnemyCell(int row, int col) const;
  bool allShipsSunk(const Cell board[BOARD_SIZE][BOARD_SIZE]) const;
  bool isPlayerDefeated() const;
  bool isEnemyDefeated() const;

private:
  // Убрали ships из параметров — генерируем напрямую
  void generateShips(Cell board[BOARD_SIZE][BOARD_SIZE]);

  Cell playerBoard[BOARD_SIZE][BOARD_SIZE];
  Cell enemyBoard[BOARD_SIZE][BOARD_SIZE];
  BotState botState;
  std::mt19937 gen;
};

#endif // GAME_H