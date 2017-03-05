#include "tile.h"

Tile::Tile(int x, int y, int value, bool empty) {
    this->x = x;
    this->y = y;
    this->value = value;
    this->empty = empty;
    QString text = QString::number(value);
    this->setStyleSheet("color: GhostWhite;"
                        "background-color: MidnightBlue;"
                        "font: bold 35px;");
    this->setText(text);
}

int Tile::getX() const {
    return x;
}

void Tile::setX(int value) {
    x = value;
}

int Tile::getY() const {
    return y;
}

void Tile::setY(int value) {
    y = value;
}

int Tile::getValue() const {
    return value;
}

void Tile::setValue(int value) {
    value = value;
}

bool Tile::isEmpty() const {
    return empty;
}

void Tile::setEmpty(bool value) {
    empty = value;
}
