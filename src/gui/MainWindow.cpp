// src/gui/MainWindow.cpp
#include "gui/MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  setWindowTitle("Морской бой — Qt версия");
  resize(800, 600);

  auto *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  auto *mainLayout = new QVBoxLayout(centralWidget);

  // Поля
  auto *boardsLayout = new QHBoxLayout();
  auto *playerWidget = new QWidget();
  auto *enemyWidget = new QWidget();
  playerLayout = new QGridLayout(playerWidget);
  enemyLayout = new QGridLayout(enemyWidget);

  // Создаём кнопки
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      // Поле игрока
      playerCells[i][j] = new QPushButton("~");
      playerCells[i][j]->setFixedSize(40, 40);
      playerCells[i][j]->setEnabled(false); // нельзя кликать по своему полю
      playerLayout->addWidget(playerCells[i][j], i, j);

      // Поле противника
      enemyCells[i][j] = new QPushButton("~");
      enemyCells[i][j]->setFixedSize(40, 40);
      connect(enemyCells[i][j], &QPushButton::clicked,
              this, [this, i, j]()
              { onPlayerCellClicked(i, j); });
      enemyLayout->addWidget(enemyCells[i][j], i, j);
    }
  }

  boardsLayout->addWidget(playerWidget);
  boardsLayout->addWidget(enemyWidget);
  mainLayout->addLayout(boardsLayout);

  // Статус
  statusLabel = new QLabel("Ваш ход. Кликните по полю противника.");
  statusLabel->setAlignment(Qt::AlignCenter);
  mainLayout->addWidget(statusLabel);

  updateBoard();
}

MainWindow::~MainWindow() = default;

void MainWindow::onPlayerCellClicked(int row, int col)
{
  bool isHit = game.playerShoot(row, col);
  updateBoard();

  if (isHit)
  {
    statusLabel->setText("💥 Попал! Дополнительный ход!");
  }
  else
  {
    statusLabel->setText("💦 Мимо. Ход бота...");
    game.botTurn();
    updateBoard();
  }
  checkGameOver();
}

void MainWindow::updateBoard()
{
  // Обновляем своё поле
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      Game::Cell c = game.getPlayerCell(i, j);
      QString text;
      if (c == Game::ShipPart)
      {
        text = "S";
      }
      else if (c == Game::Hit)
      {
        text = "X";
      }
      else if (c == Game::Miss)
      {
        text = ".";
      }
      else
      {
        text = "~";
      }
      playerCells[i][j]->setText(text);
    }
  }

  // Обновляем поле противника (корабли скрыты!)
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      Game::Cell c = game.getEnemyCell(i, j);
      QString text;
      if (c == Game::Hit)
      {
        text = "X";
      }
      else if (c == Game::Miss)
      {
        text = ".";
      }
      else
      {
        text = "~";
      }
      enemyCells[i][j]->setText(text);
    }
  }
}

void MainWindow::checkGameOver()
{
  if (game.isEnemyDefeated())
  {
    QMessageBox::information(this, "Победа!", "Вы потопили все корабли!");
    game.reset();
    updateBoard();
    statusLabel->setText("Новая игра! Ваш ход.");
  }
  else if (game.isPlayerDefeated())
  {
    QMessageBox::information(this, "Поражение!", "Бот потопил все ваши корабли!");
    game.reset();
    updateBoard();
    statusLabel->setText("Новая игра! Ваш ход.");
  }
}