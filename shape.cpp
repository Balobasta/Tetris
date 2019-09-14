#include "shape.h"

Shape::Shape(int type, QColor color, int fieldW){
    int centralX = fieldW/2;
    switch(type){
    case 1:{
        // 000
        //  0
        Tile t1 = Tile{color, centralX,-2};
        Tile t2 = Tile{color, centralX - 1, -2};
        Tile t3 = Tile{color, centralX + 1, -2};
        Tile t4 = Tile{color, centralX, -1};
        tiles.append(t1);
        tiles.append(t2);
        tiles.append(t3);
        tiles.append(t4);
        center = t1;
        break;
    }
    case 2:{
        // 0000
        Tile t1 = Tile{color, centralX, -1};
        Tile t2 = Tile{color, centralX - 1, -1};
        Tile t3 = Tile{color, centralX + 1, -1};
        Tile t4 = Tile{color, centralX + 2, -1};
        tiles.append(t1);
        tiles.append(t2);
        tiles.append(t3);
        tiles.append(t4);
        center = t1;
        break;
    }
    case 3:{
        // 00
        // 00
        Tile t1 = Tile{color, centralX, -2};
        Tile t2 = Tile{color, centralX - 1, -2};
        Tile t3 = Tile{color, centralX, -1};
        Tile t4 = Tile{color, centralX -1, -1};
        tiles.append(t1);
        tiles.append(t2);
        tiles.append(t3);
        tiles.append(t4);
        center = t1;
        break;
    }
    case 4:{
        //   0
        // 000
        Tile t1 = Tile{color, centralX + 1, -2};
        Tile t2 = Tile{color, centralX, -1};
        Tile t3 = Tile{color, centralX + 1, -1};
        Tile t4 = Tile{color, centralX -1, -1};
        tiles.append(t1);
        tiles.append(t2);
        tiles.append(t3);
        tiles.append(t4);
        center = t2;
        break;
    }
    case 5:{
        // 0
        // 000
        Tile t1 = Tile{color, centralX - 1, -2};
        Tile t2 = Tile{color, centralX, -1};
        Tile t3 = Tile{color, centralX + 1, -1};
        Tile t4 = Tile{color, centralX -1, -1};
        tiles.append(t1);
        tiles.append(t2);
        tiles.append(t3);
        tiles.append(t4);
        center = t2;
        break;
    }
    case 6:{
        //  00
        // 00
        Tile t1 = Tile{color, centralX, -2};
        Tile t2 = Tile{color, centralX + 1, -2};
        Tile t3 = Tile{color, centralX, -1};
        Tile t4 = Tile{color, centralX -1, -1};
        tiles.append(t1);
        tiles.append(t2);
        tiles.append(t3);
        tiles.append(t4);
        center = t3;
        break;
    }
    case 7:{
        //  00
        //   00
        Tile t1 = Tile{color, centralX - 1, -2};
        Tile t2 = Tile{color, centralX, -2};
        Tile t3 = Tile{color, centralX, -1};
        Tile t4 = Tile{color, centralX + 1, -1};
        tiles.append(t1);
        tiles.append(t2);
        tiles.append(t3);
        tiles.append(t4);
        center = t3;
        break;
    }
    }
}

int Shape::getMaxY(){
    int Y = 0;
    for ( int i = 0; i < tiles.size(); i++){
        if (tiles[i].y > Y)
            Y = tiles[i].y;
    }
    return Y;
}

int Shape::getLeftX(int fieldW){
    int left = fieldW;
    for( int i = 0; i < tiles.size(); i++){
        if (tiles[i].x < left)
            left = tiles[i].x;
    }
    return left;
}

int Shape::getRightX(){
    int right = 0;
    for (int i = 0; i < tiles.size(); i++){
        if (tiles[i].x > right)
            right = tiles[i].x;
    }
    return right;
}

QPair<int, int> Shape::getCenter(){
    return QPair<int, int> {center.x, center.y};
}

