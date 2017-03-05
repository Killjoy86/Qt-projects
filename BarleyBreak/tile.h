#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QPushButton>

class Tile : public QPushButton
{
    Q_OBJECT
public:
    explicit Tile(int x, int y, int value, bool empty);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getValue() const;
    void setValue(int value);

    bool isEmpty() const;
    void setEmpty(bool value);

private:
    int x;
    int y;
    int value;
    bool empty;
signals:

public slots:
};

#endif // TILE_H
