#ifndef FIELD_H
#define FIELD_H
#include <QColor>
#include <QPainter>
#include <QDebug>
#include <QDateTime>
#include "shape.h"
#include "gamestyles.h"


class field
{
public:
    field();
    void draw(QPainter &painter, int w, int h);
    void drawTile(QPainter &painter, QColor color, int j, int i, int width, int leftIndent, int upperIndent);
    void moveDown();
    bool isPause();
    void setPause(bool x);
    bool moveLeft();
    bool moveRight();
    bool rotate();
    void levelUp();
    int getLevel();
    int getPoints();
    void newGame();
    int getLines();
    GameStyle gameStyle;
private:
    void drawNewItemWindow(QPainter &painter, int upperIndent);
    bool intersectStaticTiles(Shape *shape);
    void deleteFullLayer(int num);
    Shape *currentShape;
    Shape *futureShape;
    const int w = 10;
    const int h = 20;
    Tile *staticTile[20][15];
    int minYLayer = h;
    bool lose = false;
    bool pause = false;
    int lines = 0;
    int points = 0;
    int level = 0;
};

#endif // FIELD_H
