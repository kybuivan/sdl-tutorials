#ifndef _position
#define _position

#include <string>

struct Position
{
    int col;
    int row;

    Position();
    Position(int col, int row);
    void setPosition(int x, int y);
};

#endif
