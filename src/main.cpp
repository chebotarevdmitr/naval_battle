/**
 * Проект: naval_battle
 * Этап 4: Добавление корабля противника и логика попадания
 * Цель: научиться отличать "попал" от "мимо" и обновлять состояние игры
 */

#include <iostream>
#include <string>
#include <cctype>

const int BOARD_SIZE = 10;

// Функция вывода поля
void printBoard(const char board[BOARD_SIZE][BOARD_SIZE], const std::string &title)
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

// Парсинг координат: "D5" → row=3, col=5
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
    return false; // не поддерживаем "A10"

  return (outRow >= 0 && outRow < BOARD_SIZE && outCol >= 0 && outCol < BOARD_SIZE);
}

// Инициализация поля противника с одним кораблём
void initEnemyBoard(char enemyBoard[BOARD_SIZE][BOARD_SIZE])
{
  // Заполняем водой
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      enemyBoard[i][j] = '~';
    }
  }
  // Ставим один однопалубный корабль (например, в D5 → [3][5])
  enemyBoard[3][5] = 'S'; // Ship
}

int main()
{
  char playerBoard[BOARD_SIZE][BOARD_SIZE];
  char enemyBoard[BOARD_SIZE][BOARD_SIZE];

  // Инициализация
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      playerBoard[i][j] = '~';
    }
  }
  initEnemyBoard(enemyBoard); // ← здесь появляется корабль!

  std::string input;
  int row, col;

  while (true)
  {
    printBoard(playerBoard, "Ваше поле");
    printBoard(enemyBoard, "Поле противника (S = скрытый корабль — не для показа!)");

    // На самом деле в бою игрок НЕ видит 'S' — покажем только для отладки
    // Позже мы скроем корабли и будем показывать только результаты выстрелов

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

    // Проверяем, стреляли ли уже сюда
    if (enemyBoard[row][col] == 'X' || enemyBoard[row][col] == '.')
    {
      std::cout << "⚠️  Сюда уже стреляли!\n";
      continue;
    }

    // Логика выстрела
    if (enemyBoard[row][col] == 'S')
    {
      std::cout << "💥 Попал! Дополнительный ход!\n";
      enemyBoard[row][col] = 'X'; // попадание
                                  // ← здесь НЕ выходим из цикла → игрок стреляет снова
    }
    else
    {
      std::cout << "💦 Мимо! Ход противника... (позже добавим ИИ)\n";
      enemyBoard[row][col] = '.';
      // ← здесь можно было бы передать ход боту, но пока просто ждём следующего ввода
    }
  }

  return 0;
}