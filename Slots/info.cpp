#include "info.h"

Info* Info::instance = NULL;

Info::Info(QWidget *parent) : QWidget(parent) {
    this->resize(400, 340);
    this->setWindowTitle("Pay table");

    slotChangeLeft();
}

Info::~Info() {
    instance = NULL;
    delete image;
}

Info *Info::getInfo(QWidget *parent) {
    if ( instance == NULL ) {
        instance = new Info(parent);
    }
    return instance;
}

void Info::slotChangeLeft() {
    changeRight = new QPushButton(">", this);
    changeRight->setGeometry(380, 160, 20, 40);
    changeRight->setStyleSheet("background: blue");
    changeRight->setShortcut(Qt::Key_Right);
    changeRight->show();

    close = new QPushButton("X", this);
    close->setGeometry(380, 0, 20, 20);
    close->setStyleSheet("background: red;"
                         "border-radius: 10px");
    close->show();

    image = new QImage(":/img/pay1.png");
    image->scaled(this->width(), this->height() - 20, Qt::IgnoreAspectRatio);
    lblFist = new QLabel(this);
    lblFist->setGeometry(20, 15, this->width()-40, this->height()-30);
    lblFist->setPixmap(QPixmap::fromImage(*image, Qt::AutoColor));
    lblFist->show();

    connect(changeRight, SIGNAL(clicked(bool)), this, SLOT(slotChangeRight()));
    connect(close, SIGNAL(clicked(bool)), this, SLOT(deleteLater()));
}

void Info::slotChangeRight() {

    close->hide();
    delete close;
    changeRight->hide();
    delete changeRight;
    lblFist->hide();
    delete lblFist;
    delete image;

    changeLeft = new QPushButton("<", this);
    changeLeft->setGeometry(0, 160, 20, 40);
    changeLeft->setStyleSheet("background: blue");
    changeLeft->setShortcut(Qt::Key_Left);
    changeLeft->show();

    close = new QPushButton("X", this);
    close->setGeometry(380, 0, 20, 20);
    close->setStyleSheet("background: red;"
                         "border-radius: 10px");
    close->show();

    image = new QImage(":/img/pay2.png");
    image->scaled(this->width(), this->height() - 20, Qt::IgnoreAspectRatio);
    lblSecond = new QLabel(this);
    lblSecond->setGeometry(20, 15, this->width()-40, this->height()-30);
    lblSecond->setPixmap(QPixmap::fromImage(*image, Qt::AutoColor));
    lblSecond->show();

    connect(changeLeft, SIGNAL(clicked(bool)), this, SLOT(slotShowLeft()));
    connect(close, SIGNAL(clicked(bool)), this, SLOT(deleteLater()));

}

void Info::slotShowLeft() {
    close->hide();
    delete close;
    changeLeft->hide();
    delete changeLeft;
    lblSecond->hide();
    delete lblSecond;
    delete image;

    slotChangeLeft();
}
