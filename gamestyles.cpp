#include "gamestyles.h"

GameStyle::GameStyle()
{

}

bool GameStyle::TileFixedColor(){
    return isTileColorFixed;
}

void GameStyle::setDarkStyle(){
    loseTextColor = Qt::white;
    isTileColorFixed = false;
    backgroundColor = Qt::black;
    gridColor = QColor(70, 70, 70);
    ItemWindowBorderColor = Qt::red;
    ItemWindowColor = Qt::black;
    setLoseTextColor();
}

void GameStyle::setLightStyle()
{
    loseTextColor = Qt::black;
    isTileColorFixed = false;
    backgroundColor = Qt::white;
    gridColor = Qt::cyan;
    ItemWindowBorderColor = Qt::yellow;
    ItemWindowColor = Qt::black;
    setLoseTextColor();
}

void GameStyle::setIndianStyle()
{
    loseTextColor = Qt::white;
    isTileColorFixed = false;
    backgroundColor = QColor(255, 85, 0);
    gridColor = Qt::cyan;
    ItemWindowBorderColor = Qt::yellow;
    ItemWindowColor = backgroundColor;
    setLoseTextColor();
}

void GameStyle::setSpecialStyle()
{
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    loseTextColor = QColor(qrand()%256, qrand()%256, qrand()%256);
    isTileColorFixed = qrand()%2;
    backgroundColor = QColor(qrand()%256, qrand()%256, qrand()%256);
    gridColor = QColor(qrand()%256, qrand()%256, qrand()%256);
    ItemWindowBorderColor = QColor(qrand()%256, qrand()%256, qrand()%256);;
    ItemWindowColor = QColor(qrand()%256, qrand()%256, qrand()%256);
    tileType = static_cast<TileType>(qrand()%3);
    setLoseTextColor();
}



void GameStyle::setTileFixedColor(QColor color){
    isTileColorFixed = true;
    fixedTileColor = color;
}

void GameStyle::setTileType(TileType type){
    this->tileType = type;
}

TileType GameStyle::getTileType()
{
    return this->tileType;
}

QColor GameStyle::getFixedTileColor()
{
    return fixedTileColor;
}

QColor GameStyle::getBackgroungColor(){
    return backgroundColor;
}

QColor GameStyle::getGridColor(){
    return gridColor;
}

QColor GameStyle::getItemWindowBorderColor(){
    return ItemWindowBorderColor;
}

QColor GameStyle::getItemWindowColor(){
    return ItemWindowColor;
}

QColor GameStyle::getLoseTextColor()
{
    return loseTextColor;
}

void GameStyle::setLoseTextColor()
{
    int r , g, b;
    backgroundColor.getRgb(&r, &g, &b);
    loseTextColor = QColor(255 - r, 255 - g, 255 - b);
}
