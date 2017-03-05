#include "board.h"
#include "ui_board.h"
#include <QDebug>
#include <QFile>

Board::Board(QWidget *parent) : QMainWindow(parent), ui(new Ui::Board) {
    ui->setupUi(this);
    this->setWindowTitle("Пятнашки");
    this->setFixedSize(300, 350);
    this->setStyleSheet("background-color: Silver;");

    mainWidget = new MainWidget(this);
    mainMenu = new MainMenu();
    game = new Game();
    win = new WinWidget();

    mainWidget->addWidget(mainMenu);
    mainWidget->addWidget(game);
    mainWidget->addWidget(win);
    mainWidget->setCurrentWidget(mainMenu);

    connect(mainMenu, SIGNAL(finished()), this, SLOT(setWidgetGame()));
    connect(mainMenu, SIGNAL(closed()), this, SLOT(close()));
    connect(mainMenu->btnStart, SIGNAL(clicked(bool)), game, SLOT(timerStart()));
    connect(game, SIGNAL(signalBack()), this, SLOT(setWidgetMainMenu()));
    connect(game, SIGNAL(signalWin()), this, SLOT(setWidgetWin()));
    connect(win, SIGNAL(signalMainMenu()), this, SLOT(setWidgetMainMenu()));
    connect(win, SIGNAL(signaGame()), this, SLOT(setWidgetGame()));
    connect(win->getBtnYes(), SIGNAL(clicked(bool)), game, SLOT(timerClearAndShowTiles()));
    connect(win->getBtnYes(), SIGNAL(clicked(bool)), game, SLOT(shuffleBoard()));

    setDefaultStyle();
}

Board::~Board() {
    delete ui;
}

void Board::setDefaultStyle() {
    QFile styleFile(":/qss/style.qss");
    if( styleFile.open(QFile::ReadOnly) ) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheet);
    } else {
        qDebug() << "Style can't be loaded.";
    }
}

void Board::setWidgetMainMenu() {
    mainWidget->setCurrentWidget(mainMenu);
}

void Board::setWidgetGame() {
    mainWidget->setCurrentWidget(game);
}

void Board::setWidgetWin() {
    mainWidget->setCurrentWidget(win);
    QString str = game->getTimeOfGame();
    win->setGameTime(str);
}
