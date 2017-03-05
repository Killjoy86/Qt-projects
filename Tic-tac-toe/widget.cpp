#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->setWindowTitle("Tic-tac-toe");
    imgCross = new QPixmap(":/images/cross.png");
    imgToe = new QPixmap(":/images/toe.png");
    lineH = new QPixmap(":/images/lineH.png");
    lineV = new QPixmap(":/images/lineV.png");
    lineD = new QPixmap(":/images/lineD.png");
    lineD2 = new QPixmap(":/images/lineD2.png");

    brush = new QBrush;
    palette = new QPalette;
    brush->setTextureImage(QImage(":/images/background.png"));
    palette->setBrush(QPalette::Window, *brush);
    this->setPalette(*palette);

    scene = new QGraphicsScene(QRectF(10, 10, widthOfCell*3, heightOfCell*3));
    scene->setBackgroundBrush(QColor(240, 240, 240));
    drawField(scene);

    restart = new QPushButton(tr("&Новая игра"), this);
    restart->setGeometry(250, 10, 90, 40);
    connect(restart, SIGNAL(clicked(bool)), this, SLOT(newGame()));

    quit = new QPushButton(tr("&Выход"), this);
    quit->setGeometry(250, 60, 90, 40);
    connect(quit, SIGNAL(clicked(bool)), this, SLOT(close()));

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(10, 10, widthOfCell*3, heightOfCell*3);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(gameOverHandle()));
    timer->start(100);
}

Widget::~Widget() {
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event) {
    if ( event->button() == Qt::LeftButton ) {
//        int cellX = event->x() / (225 / 3);
//        int cellY = event->y() / (225 / 3);
        if ( player == 1 ) {
            for ( int i = 0; i < 3; i++ ) {
                for ( int j = 0; j < 3; j++ ) {
                    if ( event->x() > i*(fieldSize/3)+10 && event->x() < i*(fieldSize/3)+(10+widthOfCell) &&
                         event->y() > j*(fieldSize/3)+10 && event->y() < j*(fieldSize/3)+(10+heightOfCell) &&
                         arrayField[i][j] == 0 ) {
                        scene->addPixmap(*imgCross)->setPos(i*(225/3)+11, j*(225/3)+11);
                        arrayField[i][j] = 1;
                        player = 2;
                    }
                }
            }
        } else {
            for ( int i = 0; i < 3; i++ ) {
                for ( int j = 0; j < 3; j++ ) {
                    if ( event->x() > i*(fieldSize/3)+10 && event->x() < i*(fieldSize/3)+(10+widthOfCell) &&
                         event->y() > j*(fieldSize/3)+10 && event->y() < j*(fieldSize/3)+(10+heightOfCell) &&
                         arrayField[i][j] == 0 ) {
                        scene->addPixmap(*imgToe)->setPos(i*(225/3)+11, j*(225/3)+11);
                        arrayField[i][j] = 2;
                        player = 1;
                    }
                }
            }
        }
    }
}

void Widget::drawField(QGraphicsScene *scene) {
    for ( int i = 10; i < widthOfCell*3; i += widthOfCell ) {
        for ( int j = 10; j < heightOfCell*3; j += heightOfCell ) {
            scene->addRect(i, j, widthOfCell, heightOfCell, Qt::SolidLine, Qt::NoBrush);
        }
    }
}

int Widget::gameOver() {
    // -1 - игра не окончена; 0 - ничья; 1 - победили крестики; 2 - победили нолики

    for ( int i = 1; i < 3; i++ ) {
        // По горизонтали
        if ( (arrayField[0][0] == i && arrayField[1][0] == i && arrayField[2][0] == i) ||
             (arrayField[0][1] == i && arrayField[1][1] == i && arrayField[2][1] == i) ||
             (arrayField[0][2] == i && arrayField[1][2] == i && arrayField[2][2] == i) ||

        // По вертикали
             (arrayField[0][0] == i && arrayField[0][1] == i && arrayField[0][2] == i) ||
             (arrayField[1][0] == i && arrayField[1][1] == i && arrayField[1][2] == i) ||
             (arrayField[2][0] == i && arrayField[2][1] == i && arrayField[2][2] == i) ||

        // По диагонали
             (arrayField[0][0] == i && arrayField[1][1] == i && arrayField[2][2] == i) ||
             (arrayField[2][0] == i && arrayField[1][1] == i && arrayField[0][2] == i) )
             return i;
    }
    int count = 0;
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            if ( arrayField[i][j] != 0 ) {
                count++;
            }
        }
    }
    // Заполнено все поле
    if ( count == 9 ) {
        return 0;
    }

    return -1;
}

void Widget::dialogGameOver(QString message) {
    box = new QMessageBox(this);
    box->setText(message);
    box->show();
    connect(box,SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(newGame()));
}

void Widget::newGame() {
    scene->clear();
    player = 1;
    drawField(scene);
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            arrayField[i][j] = 0;
        }
    }
    timer->start(100);
}

void Widget::gameOverHandle() {
    if ( gameOver() == 0 ) {
        dialogGameOver("Ничья");
        timer->stop();
    }
    if ( gameOver() == 1 ) {
        //По горизонтали
        if ( arrayField[0][0] == 1 && arrayField[1][0] == 1 && arrayField[2][0] == 1 ) {
            scene->addPixmap(*lineH)->setPos(0, 44);
        }
        if ( arrayField[0][1] == 1 && arrayField[1][1] == 1 && arrayField[2][1] == 1 ) {
            scene->addPixmap(*lineH)->setPos(0, 119);
        }
        if ( arrayField[0][2] == 1 && arrayField[1][2] == 1 && arrayField[2][2] == 1 ) {
            scene->addPixmap(*lineH)->setPos(0, 194);
        }
        //По вертикали
        if ( arrayField[0][0] == 1 && arrayField[0][1] == 1 && arrayField[0][2] == 1 ) {
            scene->addPixmap(*lineV)->setPos(44, 0);
        }
        if ( arrayField[1][0] == 1 && arrayField[1][1] == 1 && arrayField[1][2] == 1 ) {
            scene->addPixmap(*lineV)->setPos(119, 0);
        }
        if ( arrayField[2][0] == 1 && arrayField[2][1] == 1 && arrayField[2][2] == 1 ) {
            scene->addPixmap(*lineV)->setPos(194, 0);
        }
        //По диагонали
        if ( arrayField[0][0] == 1 && arrayField[1][1] == 1 && arrayField[2][2] == 1 ) {
            scene->addPixmap(*lineD);
        }
        if ( arrayField[2][0] == 1 && arrayField[1][1] == 1 && arrayField[0][2] == 1 ) {
            scene->addPixmap(*lineD2);
        }
        dialogGameOver("Победили крестики");
        timer->stop();
    }
    if ( gameOver() == 2 ) {
        if ( arrayField[0][0] == 2 && arrayField[1][0] == 2 && arrayField[2][0] == 2 ) {
            scene->addPixmap(*lineH)->setPos(0, 44);
        }
        if ( arrayField[0][1] == 2 && arrayField[1][1] == 2 && arrayField[2][1] == 2 ) {
            scene->addPixmap(*lineH)->setPos(0, 119);
        }
        if ( arrayField[0][2] == 2 && arrayField[1][2] == 2 && arrayField[2][2] == 2 ) {
            scene->addPixmap(*lineH)->setPos(0, 194);
        }
        //По вертикали
        if ( arrayField[0][0] == 2 && arrayField[0][1] == 2 && arrayField[0][2] == 2 ) {
            scene->addPixmap(*lineV)->setPos(44, 0);
        }
        if ( arrayField[1][0] == 2 && arrayField[1][1] == 2 && arrayField[1][2] == 2 ) {
            scene->addPixmap(*lineV)->setPos(119, 0);
        }
        if ( arrayField[2][0] == 2 && arrayField[2][1] == 2 && arrayField[2][2] == 2 ) {
            scene->addPixmap(*lineV)->setPos(194, 0);
        }
        //По диагонали
        if ( arrayField[0][0] == 2 && arrayField[1][1] == 2 && arrayField[2][2] == 2 ) {
            scene->addPixmap(*lineD);
        }
        if ( arrayField[2][0] == 2 && arrayField[1][1] == 2 && arrayField[0][2] == 2 ) {
            scene->addPixmap(*lineD2);
        }
        dialogGameOver("Победили нолики");
        timer->stop();
    }
}
