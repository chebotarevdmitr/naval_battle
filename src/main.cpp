/**
 * Проект: naval_battle
 * Этап 1: Вывод пустого игрового поля в консоли
 * Цель: научиться работать с двумерными массивами и циклами
 */

#include <iostream>

int main()
{
  const int BOARD_SIZE = 10;
  char board[BOARD_SIZE][BOARD_SIZE];

  // Заполняем всё поле символом '~' (вода)
  for (int row = 0; row < BOARD_SIZE; ++row)
  {
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
      board[row][col] = '~';
    }
  }

  // Выводим поле в консоль
  std::cout << "Игровое поле (10x10):\n";
  for (int row = 0; row < BOARD_SIZE; ++row)
  {
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
      std::cout << board[row][col] << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}