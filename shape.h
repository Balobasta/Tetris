#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>

struct Tile{
    QColor color;
    int x;
    int y;
};

class Shape
{
public:
    Shape(int type, QColor color, int fieldW);
    int getMaxY();
    int getLeftX(int fieldW);
    int getRightX();
    QPair<int, int> getCenter();
    QList<Tile> getTiles();
    QList<Tile> tiles;
    Tile center;
};

#endif // SHAPE_H
