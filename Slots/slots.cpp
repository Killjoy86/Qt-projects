#include "slots.h"

Slots::Slots(QObject *parent) : QObject(parent), QGraphicsItem() {
    currentFrame = 0;
    img = new QPixmap(":/img/reelSpin-812x196.png");

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));

}

Slots::~Slots() {

}

void Slots::start() {
    timer->start(19);
}

void Slots::stop() {
    if ( currentFrame == 58 || currentFrame == 174 || currentFrame == 290 ||
         currentFrame == 406 || currentFrame == 522 || currentFrame == 638 || currentFrame == 754) {
        timer->stop();
        nextFrame();
    } else {
        timer->stop();
    }
}

QRectF Slots::boundingRect() const {
    return QRectF(0, 0, 58, 169);
}

void Slots::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0, 0, *img, currentFrame, 0, 58, 169);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

int Slots::getCurrentFrame() const {
    return currentFrame;
}

void Slots::setCurrentFrame(int newFrame) {
    currentFrame = newFrame;
}

void Slots::nextFrame() {
    currentFrame += 58;
    if ( currentFrame >= 812 ) {
        currentFrame = 0;
    }
    this->update(0, 0, 58, 169);
}
