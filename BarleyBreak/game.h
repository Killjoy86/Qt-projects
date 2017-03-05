#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include <QTimer>
#include <QLabel>
#include <QTimerEvent>

#include "tile.h"

class MainMenu;

enum direct {
    DOWN = 0,
    LEFT,
    RIGHT,
    UP,
};

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);
    ~Game();

    Tile *findEmpty();
    Tile* findTile(int x, int y);
    void fillTheGameBoard();
    void swapTiles(int fromX, int fromY, int toX, int toY);
    bool gameIsOver();
    QString getTimeOfGame() const;

private:
    QPushButton *btnBack;
    QPushButton *btnReplace;
    QPushButton *btnPause;
    QGridLayout *layoutField;
    QHBoxLayout *additionalyMenu;
    QVBoxLayout *gameLayout;
    std::vector<Tile*>* tiles;
    int timerId;
    QLabel *timerLabel;
    QTime *currTime;
    QTimer *timer;

signals:
    void signalBack();
    void signalWin();

public slots:
    void emitBack();
    void moveTile();
    void shuffleBoard();
    void removeAllChilds();
    void slotTimer();
    void timerStart();
    void timerStop();
    void timerClearAndShowTiles();
    void pause();
};

#endif // GAME_H
