
#include "Game.h"
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
  generateShips(playerBoard);
  generateShips(enemyBoard);
}

// Проверка, можно ли поставить корабль длины `size` от (row, col) в направлении (dr, dc)
bool canPlaceShipHere(const Game::Cell board[BOARD_SIZE][BOARD_SIZE], int row, int col, int dr, int dc, int size)
{
  for (int i = 0; i < size; ++i)
  {
    int r = row + dr * i;
    int c = col + dc * i;
    if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE)
      return false;
    // Проверяем саму клетку и 3x3 вокруг
    for (int dr2 = -1; dr2 <= 1; ++dr2)
    {
      for (int dc2 = -1; dc2 <= 1; ++dc2)
      {
        int nr = r + dr2;
        int nc = c + dc2;
        if (nr < 0 || nr >= BOARD_SIZE || nc < 0 || nc >= BOARD_SIZE)
          continue;
        if (board[nr][nc] == Game::ShipPart)
          return false;
      }
    }
  }
  return true;
}

void Game::generateShips(Cell board[BOARD_SIZE][BOARD_SIZE])
{
  // Очистка
  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      board[i][j] = Game::Water;

  // Классический флот
  std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
  std::uniform_int_distribution<> rowDis(0, BOARD_SIZE - 1);
  std::uniform_int_distribution<> colDis(0, BOARD_SIZE - 1);
  std::uniform_int_distribution<> dirDis(0, 1); // 0 — горизонт, 1 — вертикаль

  for (int size : shipSizes)
  {
    bool placed = false;
    int attempts = 0;
    while (!placed && attempts < 200)
    {
      int row = rowDis(gen);
      int col = colDis(gen);
      bool horizontal = dirDis(gen) == 0;
      int dr = horizontal ? 0 : 1;
      int dc = horizontal ? 1 : 0;

      if (canPlaceShipHere(board, row, col, dr, dc, size))
      {
        for (int i = 0; i < size; ++i)
        {
          int r = row + dr * i;
          int c = col + dc * i;
          board[r][c] = Game::ShipPart;
        }
        placed = true;
      }
      attempts++;
    }
  }
}

bool Game::playerShoot(int row, int col)
{
  Cell &cell = enemyBoard[row][col];
  if (cell == Miss || cell == Hit)
    return false;

  if (cell == ShipPart)
  {
    cell = Hit;
    return true;
  }
  else
  {
    cell = Miss;
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

    if (cell == ShipPart)
    {
      cell = Hit;
      botState.addTargetNeighbors(row, col);
    }
    else
    {
      cell = Miss;
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
  return (c == ShipPart) ? Water : c;
}

bool Game::allShipsSunk(const Cell board[BOARD_SIZE][BOARD_SIZE]) const
{
  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      if (board[i][j] == ShipPart)
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