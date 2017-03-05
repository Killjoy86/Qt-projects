#ifndef SLOTS_H
#define SLOTS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>


class Slots : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    explicit Slots(QObject *parent = 0);
    ~Slots();

    void start();
    void stop();

    int getCurrentFrame() const;
    void setCurrentFrame(int newFrame);

public slots:
    void nextFrame();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap *img;
    int currentFrame;
    QTimer *timer;
};

#endif // SLOTS_H
