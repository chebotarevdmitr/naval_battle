/**
 * Проект: naval_battle
 * Этап 6: Добавление ИИ-бота, который стреляет по игроку
 * Цель: реализовать двухстороннюю игру — игрок ↔ бот
 */

#include <iostream>
#include <string>
#include <cctype>
#include <random>
#include <vector>

const int BOARD_SIZE = 10;
const int PLAYER_SHIPS = 2; // твои корабли
const int ENEMY_SHIPS = 3;  // корабли бота

struct Ship
{
  int row, col;
  bool isSunk() const { return true; }
};

// === Вывод полей ===

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
      char c = board[row][col];
      // Игрок видит свои корабли ('S'), попадания ('X'), промахи ('.')
      std::cout << c << ' ';
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
      if (c == 'S')
        std::cout << "~ "; // скрываем
      else
        std::cout << c << ' ';
    }
    std::cout << "|\n";
  }
}

// === Ввод и парсинг ===

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

// === Расстановка кораблей ===

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

// === Ход ИИ (бота) ===

void botTurn(char playerBoard[BOARD_SIZE][BOARD_SIZE], std::mt19937 &gen)
{
  std::uniform_int_distribution<> rowDis(0, BOARD_SIZE - 1);
  std::uniform_int_distribution<> colDis(0, BOARD_SIZE - 1);

  while (true)
  {
    int row = rowDis(gen);
    int col = colDis(gen);
    char &cell = playerBoard[row][col];

    if (cell == 'X' || cell == '.')
      continue; // уже стреляли

    std::cout << "\n🤖 Бот стреляет в " << char('A' + row) << col << "... ";

    if (cell == 'S')
    {
      std::cout << "💥 Попал!\n";
      cell = 'X';
      // Дополнительный ход — просто продолжаем цикл
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

  // Генерация кораблей
  generateShips(playerShips, playerBoard, PLAYER_SHIPS);
  generateShips(enemyShips, enemyBoard, ENEMY_SHIPS);

  // Генератор случайных чисел (общий для всей игры)
  std::random_device rd;
  std::mt19937 gen(rd());

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
      // остаёмся в цикле → игрок стреляет снова
    }
    else
    {
      std::cout << "💦 Вы промахнулись. Ход бота...\n";
      cell = '.';
      // Ход бота
      botTurn(playerBoard, gen);
    }
  }

  return 0;
}