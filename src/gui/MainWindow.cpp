// src/gui/MainWindow.cpp
#include "gui/MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QSoundEffect>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  setWindowTitle("Морской бой — Qt версия");
  resize(800, 600);

  // Голубой фон всего окна (море)
  setStyleSheet("background-color: #b3e0ff;");

  // Инициализация звуков из файловой системы
  QString hitPath = QCoreApplication::applicationDirPath() + "/../assets/hit.wav";
  QString missPath = QCoreApplication::applicationDirPath() + "/../assets/miss.wav";
  hitSound.setSource(QUrl::fromLocalFile(hitPath));
  missSound.setSource(QUrl::fromLocalFile(missPath));

  auto *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  centralWidget->setStyleSheet("background-color: #b3e0ff;"); // фон центральной области

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
      playerCells[i][j]->setEnabled(false);
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
  statusLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #003366;");
  mainLayout->addWidget(statusLabel);

  updateBoard();
}

MainWindow::~MainWindow() = default;

void MainWindow::playHitSound()
{
  hitSound.play();
}

void MainWindow::playMissSound()
{
  missSound.play();
}

void MainWindow::onPlayerCellClicked(int row, int col)
{
  bool isHit = game.playerShoot(row, col);
  updateBoard();

  if (isHit)
  {
    statusLabel->setText("💥 Попал! Дополнительный ход!");
    playHitSound();
  }
  else
  {
    statusLabel->setText("💦 Мимо. Ход бота...");
    playMissSound();
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
      QPushButton *btn = playerCells[i][j];

      if (c == Game::ShipPart)
      {
        btn->setText("S");
        btn->setStyleSheet("background-color: #8B4513; color: white; font-weight: bold; border: 1px solid #5a2f0f;");
      }
      else if (c == Game::Hit)
      {
        btn->setText("X");
        btn->setStyleSheet("background-color: #ff4d4d; color: white; font-weight: bold; border: 1px solid #cc0000;");
      }
      else if (c == Game::Miss)
      {
        btn->setText(".");
        btn->setStyleSheet("background-color: #f0f0f0; color: #555; border: 1px solid #ccc;");
      }
      else
      {
        btn->setText("~");
        btn->setStyleSheet("background-color: #b3e0ff; color: #2c5aa0; border: 1px solid #80c0ff;");
      }
    }
  }

  // Обновляем поле противника (корабли скрыты!)
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      Game::Cell c = game.getEnemyCell(i, j);
      QPushButton *btn = enemyCells[i][j];

      if (c == Game::Hit)
      {
        btn->setText("X");
        btn->setStyleSheet("background-color: #ff4d4d; color: white; font-weight: bold; border: 1px solid #cc0000;");
      }
      else if (c == Game::Miss)
      {
        btn->setText(".");
        btn->setStyleSheet("background-color: #f0f0f0; color: #555; border: 1px solid #ccc;");
      }
      else
      {
        btn->setText("~");
        btn->setStyleSheet("background-color: #b3e0ff; color: #2c5aa0; border: 1px solid #80c0ff;");
      }
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