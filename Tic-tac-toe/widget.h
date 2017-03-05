#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include <QPainter>

namespace Ui {
class Widget;
}

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void mousePressEvent(QMouseEvent *event);
    void drawField(QGraphicsScene* scene);
    int gameOver();
    void dialogGameOver(QString message);

private slots:
    void newGame();
    void gameOverHandle();

private:
    Ui::Widget *ui;

    QGraphicsScene* scene;

    const int widthOfCell = 75;
    const int heightOfCell = 75;
    const int fieldSize = 225;
    int arrayField[3][3] = {
                             {0, 0, 0},
                             {0, 0, 0},
                             {0, 0, 0}
                           };
    int player = 1;
    QPushButton *restart;
    QPushButton *quit;
    QPixmap* imgCross;
    QPixmap* imgToe;
    QPixmap* lineH;
    QPixmap* lineV;
    QPixmap* lineD;
    QPixmap* lineD2;
    QTimer* timer;
    QMessageBox* box;
    QBrush *brush;
    QPalette *palette;
};

#endif // WIDGET_H
