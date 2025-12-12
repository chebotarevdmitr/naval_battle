// include/gui/MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "game/Game.h"

class MainWindow : public QMainWindow
{
Q_OBJECT // ← ЭТА СТРОКА ОБЯЗАТЕЛЬНА!

    public : MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void onPlayerCellClicked(int row, int col);

private:
  void updateBoard();
  void checkGameOver();
  Game game;
  QGridLayout *playerLayout;
  QGridLayout *enemyLayout;
  QPushButton *playerCells[BOARD_SIZE][BOARD_SIZE];
  QPushButton *enemyCells[BOARD_SIZE][BOARD_SIZE];
  QLabel *statusLabel;
};

#endif // MAINWINDOW_H