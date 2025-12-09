/**
 * Проект: naval_battle
 * Этап 7: Умный ИИ с режимами "охота" и "добивание"
 * Цель: бот после попадания стреляет вокруг, чтобы уничтожить корабль
 */

#include <iostream>
#include <string>
#include <cctype>
#include <random>
#include <vector>
#include <queue>
#include <algorithm>

const int BOARD_SIZE = 10;
const int PLAYER_SHIPS = 3;
const int ENEMY_SHIPS = 3;

struct Ship
{
  int row, col;
  bool isSunk() const { return true; }
};

// === Вывод полей (без изменений) ===

void printPlayerBoard(const char board[BOARD_SIZE][BOARD_SIZE], const std::string &title)
{
  std::cout << "\n"
            << title << "\n";
  std::cout << "   ";
  for (int col = 0; col < BOARD_SIZE; ++col)
    std::cout << col << " ";
  std::cout << "\n";
  for (int row = 0; row < BOARD_SIZE; ++row)
  {
    std::cout << char('A' + row) << " |";
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
      std::cout << board[row][col] << ' ';
    }
    std::cout << "|\n";
  }
}

void printEnemyView(const char board[BOARD_SIZE][BOARD_SIZE], const std::string &title)
{
  std::cout << "\n"
            << title << " (корабли скрыты!)\n";
  std::cout << "   ";
  for (int col = 0; col < BOARD_SIZE; ++col)
    std::cout << col << " ";
  std::cout << "\n";
  for (int row = 0; row < BOARD_SIZE; ++row)
  {
    std::cout << char('A' + row) << " |";
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
      char c = board[row][col];
      std::cout << (c == 'S' ? "~ " : std::string(1, c) + " ");
    }
    std::cout << "|\n";
  }
}

// === Вспомогательные функции ===

bool parseCoordinate(const std::string &input, int &outRow, int &outCol)
{
  if (input.length() < 2)
    return false;
  char rowChar = std::toupper(static_cast<unsigned char>(input[0]));
  char colChar = input[1];
  if (rowChar < 'A' || rowChar > 'J')
    return false;
  if (!std::isdigit(static_cast<unsigned char>(colChar)))
    return false;
  outRow = rowChar - 'A';
  outCol = colChar - '0';
  if (input.length() > 2)
    return false;
  return (outRow >= 0 && outRow < BOARD_SIZE && outCol >= 0 && outCol < BOARD_SIZE);
}

bool canPlaceShip(const std::vector<Ship> &ships, int row, int col)
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

void generateShips(std::vector<Ship> &ships, char board[BOARD_SIZE][BOARD_SIZE], int count)
{
  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      board[i][j] = '~';

  ships.clear();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, BOARD_SIZE - 1);

  int attempts = 0;
  while ((int)ships.size() < count && attempts < 1000)
  {
    int r = dis(gen), c = dis(gen);
    if (canPlaceShip(ships, r, c))
    {
      ships.push_back({r, c});
      board[r][c] = 'S';
    }
    attempts++;
  }
}

// === Умный ИИ ===

struct BotState
{
  std::queue<std::pair<int, int>> targetQueue; // очередь клеток для "добивания"
  std::vector<std::vector<bool>> shot;         // где уже стреляли

  BotState()
  {
    shot.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));
  }

  bool hasShot(int row, int col) const
  {
    return shot[row][col];
  }

  void markShot(int row, int col)
  {
    shot[row][col] = true;
  }

  // Добавить соседние клетки после попадания
  void addTargetNeighbors(int hitRow, int hitCol)
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
};

void botTurn(char playerBoard[BOARD_SIZE][BOARD_SIZE], BotState &state, std::mt19937 &gen)
{
  std::uniform_int_distribution<> rowDis(0, BOARD_SIZE - 1);
  std::uniform_int_distribution<> colDis(0, BOARD_SIZE - 1);

  while (true)
  {
    int row, col;

    // Если есть цели — стреляем по ним
    if (!state.targetQueue.empty())
    {
      auto target = state.targetQueue.front();
      state.targetQueue.pop();
      row = target.first;
      col = target.second;

      // Убедимся, что ещё не стреляли (на всякий случай)
      if (state.hasShot(row, col))
        continue;
    }
    else
    {
      // Иначе — случайный поиск
      do
      {
        row = rowDis(gen);
        col = colDis(gen);
      } while (state.hasShot(row, col));
    }

    // Отмечаем выстрел
    state.markShot(row, col);

    char &cell = playerBoard[row][col];
    std::cout << "\n🤖 Бот стреляет в " << char('A' + row) << col << "... ";

    if (cell == 'S')
    {
      std::cout << "💥 Попал!\n";
      cell = 'X';
      // Добавляем соседей в очередь — начинаем "добивание"
      state.addTargetNeighbors(row, col);
      // Бот стреляет снова (остаёмся в цикле)
    }
    else
    {
      std::cout << "💦 Мимо.\n";
      cell = '.';
      break; // промах → ход заканчивается
    }
  }
}

// === Основная функция ===

int main()
{
  char playerBoard[BOARD_SIZE][BOARD_SIZE];
  char enemyBoard[BOARD_SIZE][BOARD_SIZE];
  std::vector<Ship> playerShips, enemyShips;

  generateShips(playerShips, playerBoard, PLAYER_SHIPS);
  generateShips(enemyShips, enemyBoard, ENEMY_SHIPS);

  std::random_device rd;
  std::mt19937 gen(rd());
  BotState botState; // ← состояние ИИ сохраняется между ходами!

  std::string input;
  int row, col;

  while (true)
  {
    printPlayerBoard(playerBoard, "Ваше поле (S = ваш корабль)");
    printEnemyView(enemyBoard, "Поле противника");

    std::cout << "\nВаш ход. Введите координату (например, D5) или 'quit': ";
    std::cin >> input;

    if (input == "quit")
    {
      std::cout << "Игра завершена.\n";
      break;
    }

    if (!parseCoordinate(input, row, col))
    {
      std::cout << "❌ Неверный формат! Пример: A0, J9\n";
      continue;
    }

    char &cell = enemyBoard[row][col];
    if (cell == 'X' || cell == '.')
    {
      std::cout << "⚠️  Сюда уже стреляли!\n";
      continue;
    }

    if (cell == 'S')
    {
      std::cout << "💥 Вы попали! Дополнительный ход!\n";
      cell = 'X';
    }
    else
    {
      std::cout << "💦 Вы промахнулись. Ход бота...\n";
      cell = '.';
      botTurn(playerBoard, botState, gen);
    }
  }

  return 0;
}