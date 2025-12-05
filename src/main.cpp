/**
 * Проект: naval_battle
 * Этап 3: Ввод координат игрока и обработка выстрела
 * Цель: научиться парсить ввод (например, "D5") и обновлять поле противника
 */

#include <iostream>
#include <string>
#include <cctype> // для isdigit, toupper

const int BOARD_SIZE = 10;

// Функция вывода поля (как в шаге 2)
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

// Функция парсинга координат: "D5" -> row=3, col=5
bool parseCoordinate(const std::string &input, int &outRow, int &outCol)
{
  if (input.length() < 2)
    return false;

  char rowChar = std::toupper(static_cast<unsigned char>(input[0]));
  char colChar = input[1];

  // Проверяем: первая — буква A-J, вторая — цифра 0-9
  if (rowChar < 'A' || rowChar > 'J')
    return false;
  if (!std::isdigit(static_cast<unsigned char>(colChar)))
    return false;

  outRow = rowChar - 'A';
  outCol = colChar - '0';

  // Дополнительная проверка на двузначные числа (например, "A10") — пока не поддерживаем
  if (input.length() > 2)
  {
    // Например, "A10" — попытка обработать, но у нас поле 0-9
    if (input.length() == 3 && input[1] == '1' && input[2] == '0')
    {
      outCol = 10; // но это выходит за пределы
    }
    return false; // временно отключаем двузначные
  }

  return (outRow >= 0 && outRow < BOARD_SIZE && outCol >= 0 && outCol < BOARD_SIZE);
}

int main()
{
  char playerBoard[BOARD_SIZE][BOARD_SIZE];
  char enemyBoard[BOARD_SIZE][BOARD_SIZE];

  // Инициализация полей
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      playerBoard[i][j] = '~';
      enemyBoard[i][j] = '~'; // у противника пока нет кораблей → всегда мимо
    }
  }

  std::string input;
  int row, col;

  while (true)
  {
    printBoard(playerBoard, "Ваше поле");
    printBoard(enemyBoard, "Поле противника");

    std::cout << "\nВведите координату для выстрела (например, D5) или 'quit' для выхода: ";
    std::cin >> input;

    if (input == "quit")
    {
      std::cout << "Выход из игры.\n";
      break;
    }

    if (!parseCoordinate(input, row, col))
    {
      std::cout << "❌ Некорректный ввод! Пример: A0, J9\n";
      continue;
    }

    // Логика выстрела: пока всегда "мимо", так как кораблей нет
    if (enemyBoard[row][col] == '~')
    {
      std::cout << "💦 Мимо!\n";
      enemyBoard[row][col] = '.'; // '.' — промах
    }
    else if (enemyBoard[row][col] == '.')
    {
      std::cout << "⚠️  Сюда уже стреляли!\n";
    }

    // Здесь позже добавим: проверку корабля и "попал"
  }

  return 0;
}