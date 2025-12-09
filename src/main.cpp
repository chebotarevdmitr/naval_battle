/**
 * Проект: naval_battle
 * Этап 5: Скрытие кораблей противника + случайная расстановка
 * Цель: игрок видит только результаты выстрелов, корабли — скрыты
 */

#include <iostream>
#include <string>
#include <cctype>
#include <random>
#include <vector>

const int BOARD_SIZE = 10;
const int NUM_SHIPS = 3; // Начнём с 3 однопалубных кораблей

// Вспомогательная структура для хранения корабля (пока только однопалубные)
struct Ship
{
  int row, col;
  bool isSunk() const { return true; } // однопалубный — сразу убит при попадании
};

// Функция вывода поля — НО скрывает корабли противника!
void printPlayerBoard(const char board[BOARD_SIZE][BOARD_SIZE], const std::string &title)
{
  std::cout << "\n"
            << title << "\n";
  std::cout << "   ";
  for (int col = 0; col < BOARD_SIZE; ++col)
  {
    std::cout << col << " ";
  }
  std::cout << "\n";
  for (int row = 0; row < BOARD_SIZE; ++row)
  {
    char rowLabel = 'A' + row;
    std::cout << rowLabel << " |";
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
      std::cout << board[row][col] << ' ';
    }
    std::cout << "|\n";
  }
}

// Для противника: показываем ТОЛЬКО выстрелы, корабли скрыты!
void printEnemyView(const char board[BOARD_SIZE][BOARD_SIZE], const std::string &title)
{
  std::cout << "\n"
            << title << " (корабли скрыты!)\n";
  std::cout << "   ";
  for (int col = 0; col < BOARD_SIZE; ++col)
  {
    std::cout << col << " ";
  }
  std::cout << "\n";
  for (int row = 0; row < BOARD_SIZE; ++row)
  {
    char rowLabel = 'A' + row;
    std::cout << rowLabel << " |";
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
      char cell = board[row][col];
      // Скрываем корабли ('S') — показываем только результаты выстрелов
      if (cell == 'S')
      {
        std::cout << "~ "; // как будто клетка не исследована
      }
      else
      {
        std::cout << cell << ' '; // '.' или 'X'
      }
    }
    std::cout << "|\n";
  }
}

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

// Проверка, можно ли поставить корабль в (row, col): не на краю других кораблей
bool canPlaceShip(const std::vector<Ship> &ships, int row, int col)
{
  // Проверяем вокруг: 3x3 область
  for (int dr = -1; dr <= 1; ++dr)
  {
    for (int dc = -1; dc <= 1; ++dc)
    {
      int r = row + dr;
      int c = col + dc;
      if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE)
        continue;
      // Есть ли там уже корабль?
      for (const auto &ship : ships)
      {
        if (ship.row == r && ship.col == c)
        {
          return false;
        }
      }
    }
  }
  return true;
}

// Генерация случайных кораблей (однопалубных)
void generateEnemyShips(std::vector<Ship> &ships, char enemyBoard[BOARD_SIZE][BOARD_SIZE])
{
  // Очистка
  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      enemyBoard[i][j] = '~';

  ships.clear();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, BOARD_SIZE - 1);

  int attempts = 0;
  while (ships.size() < NUM_SHIPS && attempts < 1000)
  {
    int row = dis(gen);
    int col = dis(gen);
    if (canPlaceShip(ships, row, col))
    {
      ships.push_back({row, col});
      enemyBoard[row][col] = 'S';
    }
    attempts++;
  }
}

int main()
{
  char playerBoard[BOARD_SIZE][BOARD_SIZE];
  char enemyBoard[BOARD_SIZE][BOARD_SIZE];
  std::vector<Ship> enemyShips;

  // Инициализация игрока (пока пусто)
  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      playerBoard[i][j] = '~';

  // Генерация кораблей противника
  generateEnemyShips(enemyShips, enemyBoard);

  std::string input;
  int row, col;

  while (true)
  {
    printPlayerBoard(playerBoard, "Ваше поле");
    printEnemyView(enemyBoard, "Поле противника");

    std::cout << "\nВведите координату для выстрела (например, D5) или 'quit': ";
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
      std::cout << "💥 Попал! Дополнительный ход!\n";
      cell = 'X';
      // Проверка: убит ли корабль? (для однопалубного — да)
    }
    else
    {
      std::cout << "💦 Мимо! Ход противника... (скоро добавим ИИ)\n";
      cell = '.';
    }
  }

  return 0;
}