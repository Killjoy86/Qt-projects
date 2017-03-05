#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>

class Info : public QWidget {
    Q_OBJECT
public:
    explicit Info(QWidget *parent = 0);
    ~Info();

    static Info* getInfo(QWidget *parent = 0);

private:
    static Info* instance;

    QPushButton* changeLeft;
    QPushButton* changeRight;
    QPushButton* close;
    QImage* image;
    QLabel* lblFist;
    QLabel* lblSecond;

public slots:
    void slotChangeLeft();
    void slotChangeRight();
    void slotShowLeft();
};

#endif // INFO_H
