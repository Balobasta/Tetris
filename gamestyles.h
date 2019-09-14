#ifndef GAMESTYLES_H
#define GAMESTYLES_H
#include <QColor>
#include <QTime>

enum TileType{
    rect,
    roundedRect,
    circle,
};

class GameStyle
{
public:
    GameStyle();
    void setDarkStyle();
    void setLightStyle();
    void setIndianStyle();
    void setSpecialStyle();
    bool TileFixedColor();
    void setTileFixedColor(QColor color);
    void setTileType(TileType type);
    TileType getTileType();
    QColor getFixedTileColor();
    QColor getBackgroungColor();
    QColor getGridColor();
    QColor getItemWindowBorderColor();
    QColor getItemWindowColor();
    QColor getLoseTextColor();
private:
    void setLoseTextColor();
    bool isTileColorFixed;
    QColor loseTextColor;
    QColor fixedTileColor;
    QColor backgroundColor;
    QColor gridColor;
    QColor ItemWindowBorderColor;
    QColor ItemWindowColor;
    TileType tileType;
};

#endif // GAMESTYLES_H
