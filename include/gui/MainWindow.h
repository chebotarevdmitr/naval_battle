// include/gui/MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QSoundEffect> // ← добавили заголовок для звуков

#include "game/Game.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void onPlayerCellClicked(int row, int col);

private:
  // Методы для звука
  void playHitSound();
  void playMissSound();

  // Игровая логика
  void updateBoard();
  void checkGameOver();

  // Данные
  Game game;
  QGridLayout *playerLayout;
  QGridLayout *enemyLayout;
  QPushButton *playerCells[BOARD_SIZE][BOARD_SIZE];
  QPushButton *enemyCells[BOARD_SIZE][BOARD_SIZE];
  QLabel *statusLabel;

  // Звуковые эффекты
  QSoundEffect hitSound;
  QSoundEffect missSound;
};

#endif // MAINWINDOW_H