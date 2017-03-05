#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QDebug>

#define MIN_BET 5
#define MAX_BET 1000

int cash = 0;
int bet = MIN_BET;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Slots Game");
    this->setFixedSize(641, 420);
    createMenu();

    isSpin = false;
    isMute = false;
    imgField = new QPixmap(":/img/field.png");
    timerStop = new QTimer(this);
    image = new QImage(":/img/soundOn.png");

    scene = new QGraphicsScene();
    scene->addPixmap(*imgField);
    scene->addPixmap(QPixmap::fromImage(*image, Qt::AutoColor));

    initSlots();
    scene->addItem(slot);
    slot->setPos(140, 93);
    scene->addItem(slot1);
    slot1->setPos(210, 93);
    scene->addItem(slot2);
    slot2->setPos(280, 93);
    scene->addItem(slot3);
    slot3->setPos(350, 93);
    scene->addItem(slot4);
    slot4->setPos(420, 93);

    initButtons();
    initLCD();
    scene->addWidget(lcdBet);
    scene->addWidget(lcdCash);
    scene->addWidget(lcdWin);

    QPen pen(Qt::red, 2);
    scene->addRect(141, 149, 336, 58, pen);
//    scene->addLine(141, 175, 477, 175, pen);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(btnBet, SIGNAL(clicked(bool)), this, SLOT(betSlot()));
    connect(btnMaxBet, SIGNAL(clicked(bool)), this, SLOT(maxBetSlot()));
    connect(btnSpin, SIGNAL(clicked(bool)), this, SLOT(startSlot()));
    connect(timerStop, SIGNAL(timeout()), this, SLOT(stopSlots()));
}

MainWindow::~MainWindow() {
    delete ui;
}

int MainWindow::compare(int arr[]) {
    // 1 - ничего
    // 2 - пара (free spin)
    // 3 - три в ряд (x5)
    // 4 - четыре в ряд (x200 || x100 || x50)
    // 5 - пять в ряд (x1000 || x750 || x500)
    // 6 - фул хаус (3-2) || (2-3) (x25)
    // 7 - две пары (x5)
    if ( arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3] && arr[3] == arr[4] ) {
        return 5;
    } else if ( (arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3]) ||
         (arr[1] == arr[2] && arr[2] == arr[3] && arr[3] == arr[4]) ) {
        return 4;
    } else if ( (arr[0] == arr[1] && arr[1] == arr[2] && arr[3] == arr[4]) ||
                (arr[0] == arr[1] && arr[2] == arr[3] && arr[3] == arr[4]) ) {
        return 6;
    } else if ( (arr[0] == arr[1] && arr[1] == arr[2]) ||
                (arr[1] == arr[2] && arr[2] == arr[3]) ||
                (arr[2] == arr[3] && arr[3] == arr[4]) ) {
        return 3;
    } else if ( (arr[0] == arr[1] && arr[2] == arr[3]) ||
                (arr[0] == arr[1] && arr[3] == arr[4]) ||
                (arr[1] == arr[2] && arr[3] == arr[4]) ) {
        return 7;
    } else if ( (arr[0] == arr[1]) ||
                (arr[1] == arr[2]) ||
                (arr[2] == arr[3]) ||
                (arr[3] == arr[4]) ) {
        return 2;
    }
    return 1;
}

void MainWindow::initLCD() {
    lcdBet = new QLCDNumber(5);
    lcdBet->setSegmentStyle(QLCDNumber::Flat);
    lcdBet->setStyleSheet("color: red; background: black;"
                          "border-style: outset;"
                          "border-width: 2px;"
                          "border-color: #E83C3A");
    lcdBet->setGeometry(275, 275, 90, 25);
    lcdBet->display(bet);

    lcdCash = new QLCDNumber(7);
    lcdCash->setSegmentStyle(QLCDNumber::Flat);
    lcdCash->setStyleSheet("color: red; background: black;"
                           "border-style: outset;"
                           "border-width: 1px;"
                           "border-color: beige");
    lcdCash->setGeometry(260, 53, 100, 30);
    lcdCash->display(cash);

    lcdWin = new QLCDNumber(7);
    lcdWin->setSegmentStyle(QLCDNumber::Flat);
    lcdWin->setStyleSheet("color: lime; background: black;"
                          "border-style: outset;"
                          "border-width: 2px;"
                          "border-color: lime");
    lcdWin->setGeometry(165, 275, 90, 25);

    lblWin = new QLabel(this);
    lblWin->setGeometry(175, 330, 90, 25);
    lblWin->setText("<b>Win</b>");
    lblWin->setAlignment(Qt::AlignCenter);
    lblWin->setStyleSheet("color: black; background: lime; border-style: outset; border-width: 1px; border-color: lime");
}

void MainWindow::initButtons() {
    btnSpin = new QPushButton("&Spin", this);
    btnSpin->setStyleSheet("background: #00ff00");
    btnSpin->setShortcut(Qt::Key_Space);
    btnSpin->setGeometry(475, 305, 50, 50);

    btnMaxBet = new QPushButton("&MaxBet", this);
    btnMaxBet->setStyleSheet("background: #FAF256");
    btnMaxBet->setGeometry(388, 330, 75, 25);

    btnBet = new QPushButton("&Bet", this);
    btnBet->setStyleSheet("background: #E83C3A");
    btnBet->setShortcut(Qt::Key_Plus);
    btnBet->setGeometry(285, 331, 90, 25);
}

void MainWindow::initSlots() {
    slot = new Slots(this);
    slot1 = new Slots(this);
    slot2 = new Slots(this);
    slot3 = new Slots(this);
    slot4 = new Slots(this);
}

void MainWindow::createMenu() {
    QMenu* menuFile = new QMenu("&Game");
    QAction* actNewGame = new QAction("&Change credits", menuFile);
    QAction* actQuit = new QAction("&Quit", menuFile);
    connect(actNewGame, SIGNAL(triggered(bool)), this, SLOT(slotNewGame()));
    connect(actQuit, SIGNAL(triggered(bool)), this, SLOT(close()));
    menuFile->addAction(actNewGame);
    menuFile->addAction(actQuit);

    QMenu* menuOption = new QMenu("&Option");
    soundMute = new QAction("&Sound OFF", menuOption);
    connect(soundMute, SIGNAL(triggered(bool)), this, SLOT(slotMute()));
    menuOption->addAction(soundMute);

    QMenu* menuHelp = new QMenu("&Help");
    QAction* actTable = new QAction("&Pay table", menuHelp);
    QAction* actAbout = new QAction("&About", menuHelp);
    connect(actTable, SIGNAL(triggered(bool)), this, SLOT(slotPayTable()));
    connect(actAbout, SIGNAL(triggered(bool)), this, SLOT(slotAbout()));
    menuHelp->addAction(actTable);
    menuHelp->addAction(actAbout);

    ui->menuBar->addMenu(menuFile);
    ui->menuBar->addMenu(menuOption);
    ui->menuBar->addMenu(menuHelp);


}

void MainWindow::betSlot() {
    if ( !isMute ) {
        QSound::play(":/sounds/click.wav");
    }
    if ( cash == 0 ) {
        bet = 0;
        lcdBet->display(bet);
        return;
    }
    if ( !isSpin ) {
        if ( lcdBet->value() >= MAX_BET ) {
            bet = MIN_BET;
            lcdBet->display(bet);
        } else if ( lcdBet->value() == 10 ) {
            bet = 25;
            lcdBet->display(bet);
        } else if( lcdBet->value() == 100 ) {
            bet = 250;
            lcdBet->display(bet);
            if ( lcdBet->value() > cash ) {
                bet = cash;
                lcdBet->display(bet);
            }
        } else if (lcdBet->value() == cash) {
            bet = MIN_BET;
            lcdBet->display(bet);
        } else if ( lcdBet->value() * 2 > cash ) {
            bet = cash;
            lcdBet->display(bet);
        } else {
            bet = lcdBet->value() * 2;
            lcdBet->display(bet);
        }
    }
}

void MainWindow::maxBetSlot() {
    if ( !isMute ) {
        QSound::play(":/sounds/click.wav");
    }
    if ( MAX_BET > cash ) {
        bet = cash;
        lcdBet->display(bet);
    } else {
        bet = MAX_BET;
        lcdBet->display(bet);
    }
}

void MainWindow::startSlot() {
    if ( cash <= 0 ) {
        slotNewGame();
        return;
    }

    if ( !isSpin ) {
        if ( !isMute ) {
            QSound::play(":/sounds/Cutout.wav");
        }
        lcdWin->display(0);
        cash -= bet;
        lcdCash->display(cash);
        slot->start();
        slot1->start();
        slot2->start();
        slot3->start();
        slot4->start();
        timerStop->start(1000);
        isSpin = true;
    }
}

void MainWindow::stopSlots() {
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int tmp = 350 + qrand() % 100;
    slot->stop();
    if ( !isMute ) {
        QSound::play(":/sounds/slots.wav");
    }
    arSlots[0] = slot->getCurrentFrame();

    QTime time;
    time.restart();
    for(;time.elapsed() < tmp;) {
        qApp->processEvents();
    }    

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int tmp1 = 350 + qrand() % 100;
    slot1->stop();
    if ( !isMute ) {
        QSound::play(":/sounds/slots.wav");
    }
    time.restart();
    for(;time.elapsed() < tmp1;) {
        qApp->processEvents();
    }
    arSlots[1] = slot1->getCurrentFrame();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int tmp2 = 350 + qrand() % 100;
    slot2->stop();
    if ( !isMute ) {
        QSound::play(":/sounds/slots.wav");
    }
    time.restart();
    for(;time.elapsed() < tmp2;) {
        qApp->processEvents();
    }
    arSlots[2] = slot2->getCurrentFrame();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int tmp3 = 350 + qrand() % 100;
    slot3->stop();
    if ( !isMute ) {
        QSound::play(":/sounds/slots.wav");
    }
    time.restart();
    for(;time.elapsed() < tmp3;) {
        qApp->processEvents();
    }
    arSlots[3] = slot3->getCurrentFrame();

    slot4->stop();
    if ( !isMute ) {
        QSound::play(":/sounds/lastSlot.wav");
    }
    time.restart();
    timerStop->stop();
    arSlots[4] = slot4->getCurrentFrame();

    isSpin = false;

    switch(compare(arSlots)) {
        case 1:
            break;
        case 2:
            cash += bet;
            lcdWin->display(bet);
            lcdCash->display(cash);
            if ( !isMute ) {
                QSound::play(":/sounds/win.wav");
            }
            break;
        case 3:
            cash += (bet * 5);
            lcdWin->display(bet*5);
            lcdCash->display(cash);
            if ( !isMute ) {
                QSound::play(":/sounds/win.wav");
            }
            break;
        case 4:
            if ( (arSlots[0] == 0 && arSlots[1] == 0 && arSlots[1] == 0 && arSlots[2] == 0 && arSlots[2] == 0 && arSlots[3] == 0) ||
                 (arSlots[1] == 0 && arSlots[2] == 0 && arSlots[2] == 0 && arSlots[3] == 0 && arSlots[3] == 0 && arSlots[4] == 0) ) {
                cash += (bet * 200);
                lcdWin->display(bet*200);
                lcdCash->display(cash);
            } else if ( (arSlots[0] == 696 && arSlots[1] == 696 && arSlots[1] == 696 && arSlots[2] == 696 && arSlots[2] == 696 && arSlots[3] == 696) ||
                        (arSlots[1] == 696 && arSlots[2] == 696 && arSlots[2] == 696 && arSlots[3] == 696 && arSlots[3] == 696 && arSlots[4] == 696) ) {
                cash += (bet * 100);
                lcdWin->display(bet*100);
                lcdCash->display(cash);
            } else {
                cash += (bet * 50);
                lcdWin->display(bet*50);
                lcdCash->display(cash);
            }
            if ( !isMute ) {
                QSound::play(":/sounds/win.wav");
            }
            break;
        case 5:
            if ( arSlots[0] == 0 &&
                 arSlots[1] == 0 &&
                 arSlots[1] == 0 &&
                 arSlots[2] == 0 &&
                 arSlots[2] == 0 &&
                 arSlots[3] == 0 &&
                 arSlots[3] == 0 &&
                 arSlots[4] == 0 ) {
                cash += (bet * 1000);
                lcdWin->display(bet*1000);
                lcdCash->display(cash);
            } else if ( arSlots[0] == 696 &&
                        arSlots[1] == 696 &&
                        arSlots[1] == 696 &&
                        arSlots[2] == 696 &&
                        arSlots[2] == 696 &&
                        arSlots[3] == 696 &&
                        arSlots[3] == 696 &&
                        arSlots[4] == 696 ) {
                cash += (bet * 750);
                lcdWin->display(bet*750);
                lcdCash->display(cash);
            } else {
                cash += (bet * 500);
                lcdWin->display(bet*500);
                lcdCash->display(cash);
            }
            if ( !isMute ) {
                QSound::play(":/sounds/win.wav");
            }
            break;
        case 6:
            cash += (bet * 25);
            lcdWin->display(bet*25);
            lcdCash->display(cash);
            if ( !isMute ) {
                QSound::play(":/sounds/win.wav");
            }
            break;
        case 7:
            cash += (bet * 5);
            lcdWin->display(bet*5);
            lcdCash->display(cash);
            if ( !isMute ) {
                QSound::play(":/sounds/win.wav");
            }
            break;
        default:
            break;
        // 1 - ничего
        // 2 - пара (free spin)
        // 3 - три в ряд (x5)
        // 4 - четыре в ряд (x200 || x100 || x50)
        // 5 - пять в ряд (x1000 || x750 || x500)
        // 6 - фул хаус (3-2) || (2-3) (x25)
        // 7 - две пары (x5)
    }
    if ( bet > cash ) {
        bet = cash;
        lcdBet->display(bet);
    }
}

void MainWindow::slotNewGame() {
    dialog = new QDialog(this);
    dialog->resize(200, 50);
    dialog->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::Drawer);
    line = new QLineEdit(this);
    QPushButton *btnOk = new QPushButton(tr("&Ok"));
    QPushButton *btnCloseDialog = new QPushButton(tr("Close"));
    QLabel *lblCredit = new QLabel();
    lblCredit->setText("Введите количество кредитов!");

    QVBoxLayout *vbxl = new QVBoxLayout();
    QHBoxLayout *hbxl = new QHBoxLayout();
    hbxl->addWidget(btnOk);
    hbxl->addWidget(btnCloseDialog);
    vbxl->addWidget(lblCredit);
    vbxl->addWidget(line);
    vbxl->addLayout(hbxl);
    dialog->setLayout(vbxl);

    MainWindow::setDisabled(true);
    dialog->setDisabled(false);
    dialog->show();
    dialog->setWindowState(Qt::WindowActive);

    connect(btnOk, SIGNAL(clicked(bool)), this, SLOT(slotSetCash()));
    connect(btnCloseDialog, SIGNAL(clicked(bool)), this, SLOT(slotCloseDialog()));

    bet = MIN_BET;
    lcdBet->display(bet);
}

void MainWindow::slotPayTable() {
    infoWidget = Info::getInfo(this);
    infoWidget->setGeometry(125, 35, 400, 340);
    infoWidget->show();
}

void MainWindow::slotSetCash() {
    int newCash = line->text().toInt();
    if ( newCash == 0 ) {
        QMessageBox *box = new QMessageBox(this);
        box->setText("Некоректный ввод");
        box->show();
        connect(box,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slotClearLine()));
        return;
    }
    cash = lcdCash->value() + newCash;
    MainWindow::setDisabled(false);
    dialog->close();
    lcdCash->display(cash);
}

void MainWindow::slotClearLine() {
    line->clear();
    dialog->setWindowState(Qt::WindowActive);
}

void MainWindow::slotCloseDialog() {
    dialog->close();
    MainWindow::setDisabled(false);
}

void MainWindow::slotMute() {
    if ( !isMute ) {
        isMute = true;
        soundMute->setText("&Sound ON");
        delete image;
        image = new QImage(":/img/soundOff.png");
        scene->addPixmap(QPixmap::fromImage(*image, Qt::AutoColor));
    } else {
        isMute = false;
        soundMute->setText("&Sound OFF");
        delete image;
        image = new QImage(":/img/soundOn.png");
        scene->addPixmap(QPixmap::fromImage(*image, Qt::AutoColor));
    }
}

void MainWindow::slotAbout() {
    QMessageBox* boxAbout = new QMessageBox(this);
    boxAbout->setText("Developer is Syrota Roman.\nAll rights reserved. 2016");
    boxAbout->setWindowTitle("About <Slots Game>");
    boxAbout->show();
}
