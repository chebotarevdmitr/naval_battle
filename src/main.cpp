/**
 * Проект: naval_battle
 * Этап 2: Вывод двух полей (игрока и противника) с нумерацией
 * Цель: сделать удобный визуальный интерфейс в консоли
 */

#include <iostream>
#include <iomanip> // для setw

const int BOARD_SIZE = 10;

// Функция для отображения одного поля с подписями
void printBoard(const char board[BOARD_SIZE][BOARD_SIZE], const std::string &title)
{
  std::cout << "\n"
            << title << "\n";

  // Заголовок столбцов (цифры 0-9)
  std::cout << "   ";
  for (int col = 0; col < BOARD_SIZE; ++col)
  {
    std::cout << std::setw(2) << col;
  }
  std::cout << "\n";

  // Строки с буквами A-J и содержимым
  for (int row = 0; row < BOARD_SIZE; ++row)
  {
    char rowLabel = 'A' + row; // A, B, C, ..., J
    std::cout << rowLabel << " |";
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
      std::cout << board[row][col] << ' ';
    }
    std::cout << "|\n";
  }
}

int main()
{
  char playerBoard[BOARD_SIZE][BOARD_SIZE];
  char enemyBoard[BOARD_SIZE][BOARD_SIZE];

  // Заполняем оба поля водой
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      playerBoard[i][j] = '~';
      enemyBoard[i][j] = '~';
    }
  }

  // Выводим оба поля
  printBoard(playerBoard, "Ваше поле");
  printBoard(enemyBoard, "Поле противника");

  return 0;
}