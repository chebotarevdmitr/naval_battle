// src/game/Game.cpp
#include "game/Game.h"
#include <algorithm>

// --- BotState ---
BotState::BotState()
{
  shot.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
}

bool BotState::hasShot(int row, int col) const
{
  return shot[row][col];
}

void BotState::markShot(int row, int col)
{
  shot[row][col] = true;
}

void BotState::addTargetNeighbors(int hitRow, int hitCol)
{
  int dx[4] = {-1, 0, 1, 0};
  int dy[4] = {0, 1, 0, -1};
  for (int i = 0; i < 4; ++i)
  {
    int nr = hitRow + dx[i];
    int nc = hitCol + dy[i];
    if (nr >= 0 && nr < BOARD_SIZE && nc >= 0 && nc < BOARD_SIZE && !hasShot(nr, nc))
    {
      targetQueue.push({nr, nc});
    }
  }
}

// --- Game ---
Game::Game() : gen(std::random_device{}())
{
  reset();
}

void Game::reset()
{
  botState = BotState();
  generateShips(playerShips, playerBoard, 3); // ⚠️ ОПЕЧАТКА!
  generateShips(enemyShips, enemyBoard, 3);
}

bool Game::canPlaceShip(const std::vector<Ship> &ships, int row, int col)
{
  for (int dr = -1; dr <= 1; ++dr)
    for (int dc = -1; dc <= 1; ++dc)
    {
      int r = row + dr, c = col + dc;
      if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE)
        continue;
      for (const auto &s : ships)
        if (s.row == r && s.col == c)
          return false;
    }
  return true;
}

void Game::generateShips(std::vector<Ship> &ships, Cell board[BOARD_SIZE][BOARD_SIZE], int count)
{
  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      board[i][j] = Cell::Water;

  ships.clear();
  std::uniform_int_distribution<> dis(0, BOARD_SIZE - 1);
  int attempts = 0;
  while ((int)ships.size() < count && attempts < 1000)
  {
    int r = dis(gen), c = dis(gen);
    if (canPlaceShip(ships, r, c))
    {
      ships.push_back({r, c});
      board[r][c] = Cell::ShipPart; // ✅
    }
    attempts++;
  }
}

bool Game::playerShoot(int row, int col)
{
  Cell &cell = enemyBoard[row][col];
  if (cell == Cell::Miss || cell == Cell::Hit)
    return false;

  if (cell == Cell::ShipPart)
  { // ✅
    cell = Cell::Hit;
    return true;
  }
  else
  {
    cell = Cell::Miss;
    return false;
  }
}

void Game::botTurn()
{
  std::uniform_int_distribution<> rowDis(0, BOARD_SIZE - 1);
  std::uniform_int_distribution<> colDis(0, BOARD_SIZE - 1);

  while (true)
  {
    int row, col;

    if (!botState.targetQueue.empty())
    {
      auto target = botState.targetQueue.front();
      botState.targetQueue.pop();
      row = target.first;
      col = target.second;
      if (botState.hasShot(row, col))
        continue;
    }
    else
    {
      do
      {
        row = rowDis(gen);
        col = colDis(gen);
      } while (botState.hasShot(row, col));
    }

    botState.markShot(row, col);
    Cell &cell = playerBoard[row][col];

    if (cell == Cell::ShipPart)
    { // ✅
      cell = Cell::Hit;
      botState.addTargetNeighbors(row, col);
    }
    else
    {
      cell = Cell::Miss;
      break;
    }
  }
}

Game::Cell Game::getPlayerCell(int row, int col) const
{
  return playerBoard[row][col];
}

Game::Cell Game::getEnemyCell(int row, int col) const
{
  Cell c = enemyBoard[row][col];
  return (c == Cell::ShipPart) ? Cell::Water : c;
}

bool Game::allShipsSunk(const Cell board[BOARD_SIZE][BOARD_SIZE]) const
{
  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      if (board[i][j] == Cell::ShipPart) // ✅
        return false;
  return true;
}

bool Game::isPlayerDefeated() const
{
  return allShipsSunk(playerBoard);
}

bool Game::isEnemyDefeated() const
{
  return allShipsSunk(enemyBoard);
}