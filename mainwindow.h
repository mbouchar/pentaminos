#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include "gamestatus.h"
#include "scene.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void gameWon();

    // Pentaminos 4
    void startPentamino4A();
    void startPentamino4B();
    void startPentamino4C();
    void startPentamino4D();
    void startPentamino4E();
    void startPentamino4F();
    void startPentamino4G();
    void startPentamino4H();
    void startPentamino4I();
    void startPentamino4J();
    void startPentamino4K();
    void startPentamino4L();

    // Pentaminos 5
    void startPentamino5A();
    void startPentamino5B();
    void startPentamino5C();
    void startPentamino5D();
    void startPentamino5E();
    void startPentamino5F();
    void startPentamino5G();
    void startPentamino5H();

    // Pentamino 12
    void startPentamino12();

protected:
    void closeEvent(QCloseEvent *event) override;
    void setGameStatus(GameStatus *status);
    void updateUi(Game::GameId gameId, GameStatus::Status gameStatus);
    void updateButton(QPushButton *button, GameStatus::Status gameStatus);

private:
    Ui::MainWindow *ui;
    Scene *scene;

    static int gridSize;
    static int scale;

    Game *game;
    GameStatus *gameStatus;

    void startGame(Game::GameId gameId);
    Game::GameId currentGameId;
};
#endif // MAINWINDOW_H
