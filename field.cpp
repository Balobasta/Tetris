#include "field.h"

field::field()
{
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    currentShape = new Shape(qrand()%7 + 1, QColor(qrand()%255, qrand()%255, qrand()%255), this->w);
    futureShape = new Shape(qrand()%7 + 1, QColor(qrand()%255, qrand()%255, qrand()%255), this->w);
    for(int i = 0; i < h; i++){
        for( int j = 0; j < w; j++)
            staticTile[i][j] = nullptr;
    }
    gameStyle.setDarkStyle();
    gameStyle.setTileType(roundedRect);
}


void field::draw(QPainter &painter, int w, int h)
{
    int sumOfIndentsX = w/3;
    int sumOfIndentsY = h/5;
    int upperIndent = static_cast<int>(0.5 * sumOfIndentsY);
    int leftIndent = sumOfIndentsX/9;
    int width = (w - sumOfIndentsX)/this->w;
    painter.fillRect(0, 0, w, h, gameStyle.getBackgroungColor());
    painter.setPen(gameStyle.getGridColor());
    for ( int i = leftIndent; i <= leftIndent + this->w * width; i += width){
        painter.drawLine(i, upperIndent, i, upperIndent + width*this->h);
    }
    for ( int i = upperIndent; i <= upperIndent + this->h * width; i += width){
        painter.drawLine(leftIndent, i, leftIndent + this->w * width, i);
    }
    for( int i = this->h - 1; i >= this->minYLayer; i--){
        for( int j = 0; j < this->w; j++){
            if (staticTile[i][j] != nullptr){
                drawTile(painter, staticTile[i][j]->color, j, i, width, leftIndent, upperIndent);
    }
        }
    }
    if (!lose){
        for(int i = 0; i < currentShape->tiles.size(); i++){
            if (currentShape->tiles[i].y < 0)
                continue;
            drawTile(painter, currentShape->tiles[i].color, currentShape->tiles[i].x, currentShape->tiles[i].y, width, leftIndent, upperIndent);
        }
    }else{
        QPen p(gameStyle.getLoseTextColor());
        QFont f;
        f.setPixelSize(100);
        painter.setPen(p);
        painter.setFont(f);
        painter.drawText(static_cast<int>(w * 0.3), static_cast<int>(h * 0.4), static_cast<int>(w * 0.7), static_cast<int>(h * 0.5), 1, "LOSE");
    }
    drawNewItemWindow(painter, upperIndent);
}

void field::drawTile(QPainter &painter, QColor color, int j, int i, int width, int leftIndent, int upperIndent)
{
    painter.setPen(Qt::black);
    if (gameStyle.TileFixedColor())
        color = gameStyle.getFixedTileColor();
    painter.setBrush(color);
    switch (gameStyle.getTileType()) {
        case rect:{
            painter.drawRect(leftIndent + j*width + 1, upperIndent + i*width + 1, width - 1, width - 1);
            break;
        }
        case roundedRect:{
            painter.drawRoundRect(leftIndent + j*width + 1, upperIndent + i*width + 1, width - 1, width - 1);
            break;
        }
        case circle:{
            painter.drawEllipse(leftIndent + j*width + 1, upperIndent + i*width + 1, width - 1, width - 1);
            break;
        }
    }
    painter.setBrush(Qt::NoBrush);
}

void field::moveDown()
{
    if (lose){
        return;
    }
    for(auto &a: currentShape->tiles){
        a.y ++;
    }
    currentShape->center.y++;
    if (intersectStaticTiles(currentShape)){
        for(auto &a : currentShape->tiles){
            if (a.y - 1 < 0){
                lose = true;
                delete currentShape;
                delete futureShape;
                futureShape = nullptr;
                currentShape = nullptr;
                return;
            }
            staticTile[a.y - 1][a.x] = new Tile{a.color, a.x, a.y};
            if(a.y - 1 < this->minYLayer)
                this->minYLayer = a.y - 1;
        }
        int i = this->h - 1;
        int fullLayerCount = 0;
        while(i >= this->minYLayer){
            bool fullLayer = true;
            for( int j = 0; j < this->w; j++){
                if (staticTile[i][j] == nullptr)
                    fullLayer = false;
            }
            if (fullLayer){
                this->lines++;
                fullLayerCount++;
                deleteFullLayer(i);
                this->minYLayer++;
            }else i--;
        }
        if (lines > 0)
            level = static_cast<int>(log(lines)/log(2.7)) + 1;
        switch(fullLayerCount){
            case 1:{
                this->points += 40*(level + 1);
                break;
            }
            case 2:{
                this->points += 100*(level + 1);
                break;
            }
            case 3:{
                this->points += 300*(level + 1);
                break;
            }
            case 4:{
                this->points += 1200*(level + 1);
                break;
            }
            default:{
                this->points += currentShape->getMaxY();
            }
        }
        delete currentShape;
        if (this->minYLayer <= 0 ){
            lose = true;
            delete futureShape;
            futureShape = nullptr;
            currentShape = nullptr;
            return;
        }
        currentShape = futureShape;
        int type = qrand()%7 + 1;
        futureShape = new Shape(type, QColor(qrand()%255, qrand()%255, qrand()%255), this->w);
    }
}

bool field::isPause()
{
    return pause;
}

void field::setPause(bool x)
{
    pause = x;
}

bool field::moveLeft()
{
    if (currentShape == nullptr)
        return false;
    if (currentShape->getLeftX(this->w) - 1 < 0)
        return false;
    for( int i = 0; i < currentShape->tiles.size(); i++){
        currentShape->tiles[i].x--;
    }
    currentShape->center.x--;
    if (intersectStaticTiles(currentShape)){
        for( int i = 0; i < currentShape->tiles.size(); i++){
            currentShape->tiles[i].x++;
        }
        currentShape->center.x++;
        return false;
    }
    return true;
}

bool field::moveRight()
{
    if (currentShape == nullptr)
        return false;
    if (currentShape->getRightX() + 1 >= this->w)
        return false;
    for( int i = 0; i < currentShape->tiles.size(); i++){
        currentShape->tiles[i].x++;
    }
    currentShape->center.x++;
    if (intersectStaticTiles(currentShape)){
        for( int i = 0; i < currentShape->tiles.size(); i++){
            currentShape->tiles[i].x--;
        }
        currentShape->center.x--;
        return false;
    }
    return true;
}

bool field::rotate()
{
    if (lose) return false;
    QPair<int, int> center = currentShape->getCenter();
    for( int i = 0; i < currentShape->tiles.size(); i++){
        int x = currentShape->tiles[i].x - center.first;
        int y = currentShape->tiles[i].y - center.second;
        currentShape->tiles[i].x = center.first - y;
        currentShape->tiles[i].y = center.second + x;
    }
    if(intersectStaticTiles(currentShape)){
        for( int i = 0; i < currentShape->tiles.size(); i++){
            int x = currentShape->tiles[i].x - center.first;
            int y = currentShape->tiles[i].y - center.second;
            currentShape->tiles[i].x = center.first + y;
            currentShape->tiles[i].y = center.second - x;
        }
        return false;
    }
    if (currentShape->getLeftX(this->w) < 0)
        moveRight();
    if (currentShape->getRightX() >= this->w)
        moveLeft();
    return true;
}

void field::levelUp()
{
    level++;
}

int field::getLevel()
{
    return level;
}

int field::getPoints()
{
    return this->points;
}

void field::newGame()
{
    for( int i = 0; i < this->h; i++)
        for(int j = 0; j < this->w; j++)
            if (staticTile[i][j] != nullptr){
                delete staticTile[i][j];
                staticTile[i][j] = nullptr;
            }
    points = 0;
    minYLayer = this->h;
    lose = false;
    pause = false;
    level = 0;
    lines = 0;
    if (currentShape)
        delete currentShape;
    if (futureShape)
        delete futureShape;
    currentShape = new Shape(qrand()%7 + 1, QColor(qrand()%255, qrand()%255, qrand()%255), this->w);
    futureShape = new Shape(qrand()%7 + 1, QColor(qrand()%255, qrand()%255, qrand()%255), this->w);
}

int field::getLines()
{
    return lines;
}

void field::drawNewItemWindow(QPainter &painter, int upperIndent)
{
    int indentY = upperIndent + 30;
    int newItemWindowWidth = 150;
    int indentX = 400;
    int newItemWindowHeight = 100;
    painter.setPen(gameStyle.getItemWindowBorderColor());
    painter.drawRect(indentX, indentY + 13, newItemWindowWidth, newItemWindowHeight);
//    painter.drawRect(w - newItemWindowWidth, indentY + 13, newItemWindowWidth, newItemWindowHeight);
    if (futureShape == nullptr)
        return;
    int width = newItemWindowWidth/7;
    int inWindowIndentY = newItemWindowHeight/5;
    int inWindowIndentX = static_cast<int>(newItemWindowWidth*0.3);
    for( int i = 0; i < futureShape->tiles.size(); i++){
        QPair<int,int> center = futureShape->getCenter();
        QColor color;
        if (gameStyle.TileFixedColor())
            color = gameStyle.getFixedTileColor();
        else color = futureShape->tiles[i].color;
        painter.setBrush(color);
        switch (gameStyle.getTileType()) {
            case rect:{
                painter.drawRect(indentX + inWindowIndentX + width*(futureShape->tiles[i].x - center.first + 1), static_cast<int>(indentY + inWindowIndentY + width*(futureShape->tiles[i].y + 2.5)), width, width);
                break;
            }
            case roundedRect:{
                painter.drawRoundRect(indentX + inWindowIndentX + width*(futureShape->tiles[i].x - center.first + 1), static_cast<int>(indentY + inWindowIndentY + width*(futureShape->tiles[i].y + 2.5)), width, width);
                break;
            }
            case circle:{
                painter.drawEllipse(indentX + inWindowIndentX + width*(futureShape->tiles[i].x - center.first + 1), static_cast<int>(indentY + inWindowIndentY + width*(futureShape->tiles[i].y + 2.5)), width, width);
                break;
            }
        }
    }
    painter.setBrush(Qt::NoBrush);
}

bool field::intersectStaticTiles(Shape *shape)
{
    if (shape == nullptr)
        return false;
    int maxShapeY = shape->getMaxY();
    if (maxShapeY == this->h)
        return true;
    if(maxShapeY < this->minYLayer)
        return false;
    for(auto &a : shape->tiles){
        if (staticTile[a.y][a.x] != nullptr)
            return true;
    }
    return false;
}

void field::deleteFullLayer(int num)
{
    if (num >= this->h || num < 0)
        return;
    for(int i = 0; i < this->w; i++){
        delete staticTile[num][i];
        staticTile[num][i] = nullptr;
    }
    for( int i = num-1; i >= this->minYLayer; i--){
        for( int j = 0; j < this->w; j++){
            if(staticTile[i][j] != nullptr){
                staticTile[i+1][j] = staticTile[i][j];
                staticTile[i][j] = nullptr;
            }
        }
    }
}
