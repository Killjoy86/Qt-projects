#include "game.h"
#include <QDebug>

Game::Game(QWidget *parent) : QWidget(parent) {
    tiles = new std::vector<Tile*>();

    btnBack = new QPushButton("Выйти", this);
    btnReplace = new QPushButton("Заново", this);
    btnPause = new QPushButton("Пауза", this);

    btnBack->setCursor(Qt::PointingHandCursor);
    btnReplace->setCursor(Qt::PointingHandCursor);
    btnPause->setCursor(Qt::PointingHandCursor);

    timer = new QTimer(this);
    timerLabel = new QLabel;
    currTime = new QTime(0, 0, 0);
    timerLabel->setText(currTime->toString("hh:mm:ss"));

    additionalyMenu = new QHBoxLayout;
    additionalyMenu->setMargin(10);
//    additionalyMenu->setSpacing(5);
    additionalyMenu->addWidget(btnBack);
    additionalyMenu->addWidget(btnReplace);
    additionalyMenu->addWidget(btnPause);
    additionalyMenu->addWidget(timerLabel);

    layoutField = new QGridLayout;
    gameLayout = new QVBoxLayout(this);
    gameLayout->addLayout(additionalyMenu);
    gameLayout->addLayout(layoutField);

    connect(btnBack, SIGNAL(clicked(bool)), this, SLOT(emitBack()));
    connect(btnBack, SIGNAL(clicked(bool)), this, SLOT(timerStop()));
    connect(btnBack, SIGNAL(clicked(bool)), this, SLOT(timerClearAndShowTiles()));
    connect(btnReplace, SIGNAL(clicked(bool)), this, SLOT(shuffleBoard()));
    connect(btnReplace, SIGNAL(clicked(bool)), this, SLOT(timerClearAndShowTiles()));
    connect(btnBack, SIGNAL(clicked(bool)), this, SLOT(removeAllChilds()));
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SLOT(pause()));

    fillTheGameBoard();
}

Game::~Game() {

}

Tile* Game::findEmpty() {
    Tile* emptyTile;
    for ( unsigned int i = 0; i < this->tiles->size(); i++ ){
        emptyTile = this->tiles->at(i);
        if ( emptyTile->isEmpty() )
            return emptyTile;
    }
    return NULL;
}

Tile *Game::findTile(int x, int y) {
    Tile *item;
    for ( int i = 0; i < 16; i++ ) {
        item = this->tiles->at(i);
        if ( item->getX() == x && item->getY() == y ) {
            return item;
        }
    }
    return NULL;
}

void Game::fillTheGameBoard() {
    int counter = 0;
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            counter++;
            Tile *tile;
            if ( counter < 16 ) {
                tile = new Tile(i, j, counter, false);
            } else {
                tile = new Tile(i, j, counter, true);
                tile->setVisible(false);
            }
            tiles->push_back(tile);
            tile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            tile->setCursor(Qt::PointingHandCursor);
            layoutField->addWidget(tile, i, j);
            connect(tile, SIGNAL(clicked(bool)), SLOT(moveTile()));
        }
    }
//    shuffleBoard();
}

void Game::shuffleBoard() {
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    int direct = 1;
    for ( int i = 0; i < 1000; i++ ) {
        direct = qrand() % 4;
        Tile *emptyPoint = findEmpty();
        int x = emptyPoint->getX();
        int y = emptyPoint->getY();
        switch (direct) {
        case DOWN:
            swapTiles(x, y, x+1, y);
            break;
        case LEFT:
            swapTiles(x, y, x, y-1);
            break;
        case UP:
            swapTiles(x, y, x-1, y);
            break;
        case RIGHT:
            swapTiles(x, y, x, y+1);
            break;
        default:
            break;
        }
    }    
}

void Game::removeAllChilds() {
    QLayoutItem *child;
    QWidget *w;
    while((child = layoutField->takeAt(0)) != 0){
        w = child->widget();
        layoutField->removeItem(child);
        delete child;
        delete w;
    }
    tiles->clear();
    fillTheGameBoard();
}

void Game::swapTiles(int fromX, int fromY, int toX, int toY) {
    if ( toX < 0 || toX > 4 )
        return;
    if ( toY < 0 || toY > 4 )
        return;
    Tile *from = findTile(fromX, fromY);
    Tile *to = findTile(toX, toY);

    if ( from == NULL || to == NULL )
        return;
    layoutField->addWidget(to, from->getX(), from->getY());
    layoutField->addWidget(from, to->getX(), to->getY());
    to->setX(fromX);
    to->setY(fromY);
    from->setX(toX);
    from->setY(toY);

}

bool Game::gameIsOver() {
    Tile* element;
    int value;
    for ( unsigned int i = 1; i <= this->tiles->size(); i++ ) {
        element = this->tiles->at(i-1);
        value = element->getX()*4+element->getY();
        if ( element->getValue()-1 != value ) {
            return false;
        }
    }
    return true;
}

QString Game::getTimeOfGame() const {
    QString str = timerLabel->text();
    return str;
}

void Game::slotTimer() {
    QTime tmp = *currTime;
    *currTime = tmp.addSecs(1);
    timerLabel->setText(currTime->toString("hh:mm:ss"));

}

void Game::timerStart() {
    currTime = new QTime(0, 0, 0);
    timer->start(1000);
}

void Game::timerStop() {
    timer->stop();
}

void Game::timerClearAndShowTiles() {
    if ( timer->isActive() ) {
        timer->stop();
    }
    currTime = new QTime(0, 0, 0);
    timerLabel->setText(currTime->toString("hh:mm:ss"));
    timer->start();
    for ( unsigned int i = 0; i < tiles->size(); i++ ) {
        Tile *tmp = tiles->at(i);
        if ( tmp->getValue() != 16 )
            tmp->show();
    }
}

void Game::pause() {
    if ( timer->isActive() ) {
        timer->stop();
        btnPause->setText("Старт");
        for ( unsigned int i = 0; i < tiles->size(); i++ ) {
            Tile *tmp = tiles->at(i);
            if ( tmp->getValue() != 16 )
                tmp->hide();
        }
    } else {
        timer->start(1000);
        btnPause->setText("Пауза");
        for ( unsigned int i = 0; i < tiles->size(); i++ ) {
            Tile *tmp = tiles->at(i);
            if ( tmp->getValue() != 16 )
                tmp->show();
        }
    }

}

void Game::moveTile() {
    Tile *emptyPoint = findEmpty();

    Tile *tmp = ((Tile*)sender());

    if ( (tmp->getX() == emptyPoint->getX() && tmp->getY() == emptyPoint->getY()-1) ||
         (tmp->getX() == emptyPoint->getX()-1 && tmp->getY() == emptyPoint->getY()) ||
         (tmp->getX() == emptyPoint->getX() && tmp->getY() == emptyPoint->getY()+1) ||
         (tmp->getX() == emptyPoint->getX()+1 && tmp->getY() == emptyPoint->getY()) ) {
        layoutField->addWidget(tmp, emptyPoint->getX(), emptyPoint->getY());
        layoutField->addWidget(emptyPoint, tmp->getX(), tmp->getY());
        int x = tmp->getX();
        int y = tmp->getY();
        tmp->setX(emptyPoint->getX());
        tmp->setY(emptyPoint->getY());
        emptyPoint->setX(x);
        emptyPoint->setY(y);
    }
    if ( gameIsOver() ) {
        signalWin();
        timerStop();
        currTime = new QTime(0, 0, 0);
        timerLabel->setText(currTime->toString("hh:mm:ss"));
    }

}

void Game::emitBack() {
    emit signalBack();
}
