#ifndef BOARD_H
#define BOARD_H

#define START_SCREEN_INDEX 0
#define GAME_SCREEN_INDEX 1
#define WINNER_SCREEN_INDEX 2


#include <QMainWindow>
#include <QStateMachine>
#include <QState>

#include "mainwidget.h"
#include "mainmenu.h"
#include "game.h"
#include "winwidget.h"

namespace Ui {
class Board;
}

class Board : public QMainWindow {
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);
    ~Board();

    void setDefaultStyle();
private:
    Ui::Board *ui;
    MainWidget* mainWidget;
    MainMenu* mainMenu;
    Game* game;
    WinWidget *win;

public slots:
    void setWidgetMainMenu();
    void setWidgetGame();
    void setWidgetWin();
};

#endif // BOARD_H
