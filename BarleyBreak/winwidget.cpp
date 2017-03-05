#include "winwidget.h"
#include <QDebug>

WinWidget::WinWidget(QWidget *parent) : QWidget(parent) {
    this->resize(300, 350);

    gameTime = "00:00:00";
    lbl = new QLabel();
    lbl->setAlignment(Qt::AlignCenter);

    btnYes = new QPushButton("Да", this);
    btnYes->setCursor(Qt::PointingHandCursor);
    btnYes->setStyleSheet("color: green;"
                          "font: bold 13px;");
    btnNo = new QPushButton("Нет", this);
    btnNo->setCursor(Qt::PointingHandCursor);
    btnNo->setStyleSheet("color: Red;"
                          "font: bold 13px;");
    vbox = new QVBoxLayout;
    hbox = new QHBoxLayout;
    hbox->addWidget(btnYes);
    hbox->addWidget(btnNo);
    vbox->addWidget(lbl);
    vbox->addLayout(hbox);
    setLayout(vbox);

    connect(btnNo, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(btnNo, SIGNAL(clicked(bool)), SLOT(emitClose()));
    connect(btnYes, SIGNAL(clicked(bool)), this, SLOT(nextGame()));
}

WinWidget::~WinWidget() {

}

void WinWidget::setGameTime(QString newTime) {
    this->gameTime = newTime;
    update();
    lbl->setText("Победа!\nВаше время " + gameTime + "\nCыграете еще?");
}

QPushButton *WinWidget::getBtnYes() const {
    return btnYes;
}

void WinWidget::emitClose() {
    emit signalMainMenu();
}

void WinWidget::nextGame() {
    emit signaGame();
}
