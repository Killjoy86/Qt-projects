#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    this->resize(300, 350);

    name = new QLabel(this);
    name->setGeometry(50, 30, 200, 50);
    name->setText("ПЯТНАШКИ");
    name->setStyleSheet("color: MidnightBlue;"
                        "font: bold 25px;"
                        "border-style: outset;"
                        "border-width: 3px;"
                        "border-radius: 10px;"
                        "border-color: GhostWhite;");
    name->setAlignment(Qt::AlignCenter);

    btnStart = new QPushButton("Новая игра", this);
    btnStart->setGeometry(50, 140, 200, 50);
    btnStart->setCursor(Qt::PointingHandCursor);

    btnExit = new QPushButton("Выход", this);
    btnExit->setGeometry(50, 210, 200, 50);
    btnExit->setCursor(Qt::PointingHandCursor);

    copyright = new QLabel(this);
    copyright->setGeometry(25, 305, 250, 50);
    copyright->setText("Copyright © 2017. All rights reserved\nfor Syrota Roman.");
    copyright->setAlignment(Qt::AlignCenter);

    connect(btnStart, SIGNAL(clicked(bool)), this, SLOT(emitSignalFinished()));
    connect(btnExit, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(btnExit, SIGNAL(clicked(bool)), this, SLOT(emitClosed()));
}

MainMenu::~MainMenu() {

}

void MainMenu::emitSignalFinished() {
    emit finished();
}

void MainMenu::emitClosed() {
    emit closed();
}
