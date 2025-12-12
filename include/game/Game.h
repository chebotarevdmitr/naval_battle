// include/game/Game.h
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <queue>
#include <random>

const int BOARD_SIZE = 10;

// Внешняя структура — остаётся как есть
struct Ship
{
  int row, col;
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
  // 🔥 ИЗМЕНЕНО: Ship → ShipPart (или просто убираем это значение!)
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
  void generateShips(std::vector<Ship> &ships, Cell board[BOARD_SIZE][BOARD_SIZE], int count);
  bool canPlaceShip(const std::vector<Ship> &ships, int row, int col);

  Cell playerBoard[BOARD_SIZE][BOARD_SIZE];
  Cell enemyBoard[BOARD_SIZE][BOARD_SIZE];
  std::vector<Ship> playerShips, enemyShips;
  BotState botState;
  std::mt19937 gen;
};

#endif // GAME_H